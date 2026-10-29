using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using xlwDotNet;

namespace DotNetInterfaceGenerator
{
    internal static class AotInterfaceGenerator
    {
        private sealed class Conversion
        {
            public MethodInfo Method { get; set; }
            public Type InputType { get; set; }
        }

        private sealed class Export
        {
            public MethodInfo Method { get; set; }
            public string EntryPoint { get; set; }
            public bool IsLifecycle { get; set; }
            public bool IsOpen { get; set; }
            public Type[] NativeParameterTypes { get; set; }
        }

        private static readonly Type[] ScalarTypes =
        {
            typeof(double), typeof(short), typeof(int), typeof(uint), typeof(bool)
        };

        private static readonly Type[] ArrayTypes =
        {
            typeof(double[]), typeof(int[]), typeof(double[,]), typeof(int[,]),
            typeof(double[][]), typeof(int[][])
        };

        public static void Generate(Assembly sourceAssembly, string libraryName, string directory, string fileName)
        {
            Type[] sourceTypes = sourceAssembly.GetExportedTypes();
            var conversions = FindConversions(sourceTypes);
            var exports = FindExports(sourceTypes, conversions);
            Directory.CreateDirectory(directory);

            File.WriteAllText(Path.Combine(directory, fileName + ".h"),
                GenerateHeader(libraryName, fileName, exports));
            File.WriteAllText(Path.Combine(directory, fileName + ".cpp"),
                GenerateNativeSource(fileName, sourceAssembly.GetName().Name + ".dll", exports, conversions));
            File.WriteAllText(Path.Combine(directory, "XlwAotExports.g.cs"),
                GenerateManagedSource(exports, conversions));
        }

        private static List<Conversion> FindConversions(IEnumerable<Type> sourceTypes)
        {
            var conversions = new List<Conversion>();
            foreach (MethodInfo method in sourceTypes.SelectMany(t => t.GetMethods())
                         .Where(m => m.IsPublic && m.IsStatic &&
                                     m.GetCustomAttributes(typeof(TypeRegisterAttribute), false).Length != 0))
            {
                ParameterInfo[] parameters = method.GetParameters();
                if (parameters.Length != 1 || !IsNativeType(parameters[0].ParameterType) ||
                    method.ReturnType == typeof(void) || IsNativeType(method.ReturnType))
                {
                    throw new InvalidOperationException(
                        "Type conversion method " + method.Name +
                        " must take one supported XLW value type and return a custom type.");
                }

                conversions.Add(new Conversion { Method = method, InputType = parameters[0].ParameterType });
            }

            return conversions;
        }

        private static List<Export> FindExports(IEnumerable<Type> sourceTypes, List<Conversion> conversions)
        {
            var methods = sourceTypes.SelectMany(t => t.GetMethods()).Where(m => m.IsPublic && m.IsStatic)
                .OrderBy(m => m.DeclaringType.FullName, StringComparer.Ordinal)
                .ThenBy(m => m.MetadataToken).ToArray();

            var exports = new List<Export>();
            var functionNames = new HashSet<string>(StringComparer.Ordinal);
            int index = 0;
            foreach (MethodInfo method in methods)
            {
                ExcelExportAttribute[] exportAttributes =
                    (ExcelExportAttribute[])method.GetCustomAttributes(typeof(ExcelExportAttribute), false);
                ExcelOnOpenAttribute[] openAttributes =
                    (ExcelOnOpenAttribute[])method.GetCustomAttributes(typeof(ExcelOnOpenAttribute), false);
                ExcelOnCloseAttribute[] closeAttributes =
                    (ExcelOnCloseAttribute[])method.GetCustomAttributes(typeof(ExcelOnCloseAttribute), false);

                if (exportAttributes.Length > 1)
                    throw new InvalidOperationException("Method must have exactly one ExcelExportAttribute.");
                if (exportAttributes.Length == 1 && (openAttributes.Length != 0 || closeAttributes.Length != 0))
                    throw new InvalidOperationException("A method cannot be both an Excel export and a lifecycle hook.");

                if (exportAttributes.Length == 1)
                {
                    if (method.ContainsGenericParameters)
                        throw new InvalidOperationException("Generic methods cannot be exported with Native AOT: " + method.Name);
                    ValidateCppIdentifier(method.Name);
                    if (!functionNames.Add(method.Name))
                        throw new InvalidOperationException("Exported method names must be unique: " + method.Name);
                    Type[] nativeParameters = method.GetParameters()
                        .Select(p => GetNativeParameterType(p.ParameterType, conversions)).ToArray();
                    if (!IsNativeType(method.ReturnType) || IsCustomType(method.ReturnType, conversions))
                        throw new InvalidOperationException("Not exporting " + method.Name + ": unsupported return type.");

                    foreach (ParameterInfo parameter in method.GetParameters())
                    {
                        if (parameter.GetCustomAttributes(typeof(ParameterAttribute), false).Length != 1)
                            throw new InvalidOperationException(
                                "Method parameters must have exactly one ParameterAttribute: " + method.Name);
                        if (parameter.ParameterType.IsByRef || parameter.IsOut)
                            throw new InvalidOperationException(
                                "By-reference parameters are not supported by Native AOT exports: " + method.Name);
                        if (!IsSupportedExportType(parameter.ParameterType) &&
                            !conversions.Any(c => c.Method.ReturnType == parameter.ParameterType))
                            throw new InvalidOperationException(
                                "Not exporting " + method.Name + ": unsupported parameter type " +
                                parameter.ParameterType.FullName);
                    }

                    exports.Add(new Export
                    {
                        Method = method,
                        EntryPoint = "xlw_aot_call_" + index++.ToString("D4"),
                        NativeParameterTypes = nativeParameters
                    });
                }

                if (openAttributes.Length + closeAttributes.Length != 0)
                {
                    if (openAttributes.Length + closeAttributes.Length > 1)
                        throw new InvalidOperationException("A method can have only one lifecycle attribute.");
                    if (method.ReturnType != typeof(void) || method.GetParameters().Length != 0)
                        throw new InvalidOperationException(
                            "Lifecycle methods must be public static void methods without parameters: " + method.Name);
                    ValidateCppIdentifier(method.Name);
                    if (!functionNames.Add(method.Name))
                        throw new InvalidOperationException("Exported method names must be unique: " + method.Name);
                    exports.Add(new Export
                    {
                        Method = method,
                        EntryPoint = "xlw_aot_call_" + index++.ToString("D4"),
                        IsLifecycle = true,
                        IsOpen = openAttributes.Length != 0
                    });
                }
            }

            return exports;
        }

        private static string GenerateHeader(string libraryName, string fileName, IEnumerable<Export> exports)
        {
            var output = new StringBuilder();
            output.AppendLine("#ifndef " + fileName.ToUpperInvariant() + "_H");
            output.AppendLine("#define " + fileName.ToUpperInvariant() + "_H");
            output.AppendLine("#define ERRCELLS_NOT_REQUIRED");
            output.AppendLine("#include <xlwDotNet.h>");
            output.AppendLine("//<xlw:libraryname=" + libraryName);
            output.AppendLine();

            foreach (Export export in exports)
            {
                if (export.IsLifecycle)
                {
                    output.AppendLine(export.IsOpen
                        ? "//<xlw:onopen( " + export.Method.Name + " )"
                        : "//<xlw:onclose( " + export.Method.Name + " )");
                    output.AppendLine();
                    continue;
                }

                ExcelExportAttribute attribute =
                    (ExcelExportAttribute)export.Method.GetCustomAttributes(typeof(ExcelExportAttribute), false)[0];
                output.AppendLine(CppType(export.Method.ReturnType) + " // " + attribute.Description);
                if (attribute.volatileFlag) output.AppendLine("//<xlw:volatile");
                if (attribute.timeFlag) output.AppendLine("//<xlw:time");
                if (attribute.threadSafeFlag) output.AppendLine("//<xlw:threadsafe");
                if (attribute.xlmCommandFlag) output.AppendLine("//<xlw:macrosheet");
                output.Append(export.Method.Name + "(");
                ParameterInfo[] parameters = export.Method.GetParameters();
                for (int i = 0; i < parameters.Length; ++i)
                {
                    ParameterAttribute attributeForParameter =
                        (ParameterAttribute)parameters[i].GetCustomAttributes(typeof(ParameterAttribute), false)[0];
                    output.Append(CppParameterType(export.NativeParameterTypes[i]) + " " + ArgumentName(i));
                    if (i + 1 != parameters.Length) output.Append(", ");
                    output.AppendLine(" // " + attributeForParameter.Description);
                }

                output.AppendLine(");");
                output.AppendLine();
            }

            output.AppendLine("#endif");
            return output.ToString();
        }

        private static string GenerateNativeSource(
            string fileName, string nativeLibraryFileName, IEnumerable<Export> exports, List<Conversion> conversions)
        {
            var output = new StringBuilder();
            output.AppendLine("#include \"" + fileName + ".h\"");
            output.AppendLine("#include <windows.h>");
            output.AppendLine("#include <cwchar>");
            output.AppendLine("#include <memory>");
            output.AppendLine("#include <stdexcept>");
            output.AppendLine("#include <string>");
            output.AppendLine("#include <vector>");
            output.AppendLine();
            output.AppendLine("static HMODULE XlwAotModule()");
            output.AppendLine("{");
            output.AppendLine("    static HMODULE module = []()");
            output.AppendLine("    {");
            output.AppendLine("        HMODULE currentModule = nullptr;");
            output.AppendLine("        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&XlwAotModule), &currentModule))");
            output.AppendLine("            throw std::runtime_error(\"Unable to locate the XLL module.\");");
            output.AppendLine("        std::vector<wchar_t> path(32768);");
            output.AppendLine("        DWORD length = GetModuleFileNameW(currentModule, path.data(), static_cast<DWORD>(path.size()));");
            output.AppendLine("        if (length == 0 || length >= path.size())");
            output.AppendLine("            throw std::runtime_error(\"Unable to locate the XLL directory.\");");
            output.AppendLine("        std::wstring libraryPath(path.data(), length);");
            output.AppendLine("        size_t separator = libraryPath.find_last_of(L\"\\\\/\");");
            output.AppendLine("        if (separator == std::wstring::npos) throw std::runtime_error(\"Unable to locate the XLL directory.\");");
            output.AppendLine("        libraryPath.resize(separator + 1);");
            output.AppendLine("        libraryPath += L\"" + nativeLibraryFileName + "\";");
            output.AppendLine("        HMODULE loadedModule = LoadLibraryW(libraryPath.c_str());");
            output.AppendLine("        if (!loadedModule)");
            output.AppendLine("            throw std::runtime_error(\"Unable to load the Native AOT library beside the XLL (Windows error \" + std::to_string(GetLastError()) + \").\");");
            output.AppendLine("        return loadedModule;");
            output.AppendLine("    }();");
            output.AppendLine("    return module;");
            output.AppendLine("}");
            output.AppendLine();
            output.AppendLine("template <typename T>");
            output.AppendLine("static T XlwGetAotFunction(const char* name)");
            output.AppendLine("{");
            output.AppendLine("    T function = reinterpret_cast<T>(GetProcAddress(XlwAotModule(), name));");
            output.AppendLine("    if (!function) throw std::runtime_error(std::string(\"Native AOT export is missing: \") + name);");
            output.AppendLine("    return function;");
            output.AppendLine("}");
            output.AppendLine();
            output.AppendLine("using XlwAotFreeFunction = void (__cdecl *)(void*);");
            output.AppendLine("static void XlwAotFree(void* value)");
            output.AppendLine("{");
            output.AppendLine("    static XlwAotFreeFunction function = XlwGetAotFunction<XlwAotFreeFunction>(\"xlw_aot_free\");");
            output.AppendLine("    function(value);");
            output.AppendLine("}");
            output.AppendLine();
            foreach (Export export in exports)
            {
                string functionType = "XlwAotFunction_" + export.EntryPoint;
                output.AppendLine(EntryPointFunctionPointerDeclaration(export));
                output.AppendLine("static " + functionType + " XlwAotCall_" + export.EntryPoint + "()");
                output.AppendLine("{");
                output.AppendLine("    static " + functionType + " function = XlwGetAotFunction<" +
                                  functionType + ">(\"" + export.EntryPoint + "\");");
                output.AppendLine("    return function;");
                output.AppendLine("}");
            }
            output.AppendLine();
            output.AppendLine("static void XlwCheckAotStatus(int status, wchar_t* error)");
            output.AppendLine("{");
            output.AppendLine("    std::unique_ptr<void, void (*)(void*)> errorOwner(error, &XlwAotFree);");
            output.AppendLine("    if (status == 0) return;");
            output.AppendLine("    std::string message(\"Native AOT C# call failed.\");");
            output.AppendLine("    if (error)");
            output.AppendLine("    {");
            output.AppendLine("        int length = WideCharToMultiByte(CP_UTF8, 0, error, -1, nullptr, 0, nullptr, nullptr);");
            output.AppendLine("        if (length > 1)");
            output.AppendLine("        {");
            output.AppendLine("            std::vector<char> utf8(static_cast<size_t>(length));");
            output.AppendLine("            WideCharToMultiByte(CP_UTF8, 0, error, -1, utf8.data(), length, nullptr, nullptr);");
            output.AppendLine("            message.assign(utf8.data());");
            output.AppendLine("        }");
            output.AppendLine("    }");
            output.AppendLine("    throw std::runtime_error(message);");
            output.AppendLine("}");
            output.AppendLine();

            foreach (Export export in exports)
            {
                if (export.IsLifecycle)
                {
                    output.AppendLine("void " + export.Method.Name + "()");
                    output.AppendLine("{");
                    output.AppendLine("    wchar_t* error = nullptr;");
                    output.AppendLine("    int status = XlwAotCall_" + export.EntryPoint + "()(&error);");
                    output.AppendLine("    XlwCheckAotStatus(status, error);");
                    output.AppendLine("}");
                    output.AppendLine();
                    continue;
                }

                output.Append(CppType(export.Method.ReturnType) + " " + export.Method.Name + "(");
                WriteCppParameters(output, export);
                output.AppendLine(")");
                output.AppendLine("{");
                foreach (ParameterInfo parameter in export.Method.GetParameters())
                    WriteCppInputSetup(output, parameter, GetNativeParameterType(parameter.ParameterType, conversions));
                WriteCppCall(output, export);
                output.AppendLine("}");
                output.AppendLine();
            }

            return output.ToString();
        }

        private static string GenerateManagedSource(IEnumerable<Export> exports, List<Conversion> conversions)
        {
            var output = new StringBuilder();
            output.AppendLine("// Generated by DotNetInterfaceGenerator. Do not edit.");
            output.AppendLine("using System;");
            output.AppendLine("using System.Runtime.CompilerServices;");
            output.AppendLine("using System.Runtime.InteropServices;");
            output.AppendLine();
            output.AppendLine("internal static unsafe class XlwAotExports");
            output.AppendLine("{");
            output.AppendLine("    [UnmanagedCallersOnly(EntryPoint = \"xlw_aot_free\", CallConvs = new[] { typeof(CallConvCdecl) })]");
            output.AppendLine("    public static void Free(void* value) => NativeMemory.Free(value);");
            output.AppendLine();

            foreach (Export export in exports)
            {
                string signature = ExportSignature(export, conversions);
                output.AppendLine("    [UnmanagedCallersOnly(EntryPoint = \"" + export.EntryPoint +
                                  "\", CallConvs = new[] { typeof(CallConvCdecl) })]");
                output.AppendLine("    public static int " + export.EntryPoint + "(" + signature + ")");
                output.AppendLine("    {");
                output.AppendLine("        if (error == null) return 1;");
                output.AppendLine("        *error = null;");
                WriteManagedBody(output, export, conversions);
                output.AppendLine("    }");
                output.AppendLine();
            }

            output.AppendLine("    private static void SetError(string message, char** error)");
            output.AppendLine("    {");
            output.AppendLine("        if (error == null) return;");
            output.AppendLine("        int length = message.Length;");
            output.AppendLine("        char* buffer = (char*)NativeMemory.Alloc((nuint)(length + 1), (nuint)sizeof(char));");
            output.AppendLine("        if (buffer == null) return;");
            output.AppendLine("        for (int i = 0; i < length; ++i) buffer[i] = message[i];");
            output.AppendLine("        buffer[length] = '\\0';");
            output.AppendLine("        *error = buffer;");
            output.AppendLine("    }");
            output.AppendLine("}");
            return output.ToString();
        }

        private static string ExportSignature(Export export, List<Conversion> conversions)
        {
            var parameters = new List<string>();
            foreach (ParameterInfo parameter in export.Method.GetParameters())
                AddManagedInputParameters(parameters, ArgumentName(parameter.Position), GetNativeParameterType(parameter.ParameterType, conversions));

            if (!export.IsLifecycle)
                AddManagedOutputParameters(parameters, export.Method.ReturnType);
            parameters.Add("char** error");
            return string.Join(", ", parameters);
        }

        private static void WriteManagedBody(StringBuilder output, Export export, List<Conversion> conversions)
        {
            output.AppendLine("        try");
            output.AppendLine("        {");
            foreach (ParameterInfo parameter in export.Method.GetParameters())
            {
                Type nativeType = GetNativeParameterType(parameter.ParameterType, conversions);
                WriteManagedInputConversion(output, ArgumentName(parameter.Position), nativeType, "            ");
            }

            string invocation = MethodExpression(export.Method) + "." + export.Method.Name + "(" +
                                string.Join(", ", export.Method.GetParameters().Select(p =>
                                    ConvertArgumentExpression(p, conversions))) + ")";
            if (export.IsLifecycle)
            {
                output.AppendLine("            " + invocation + ";");
            }
            else if (export.Method.ReturnType == typeof(void))
            {
                output.AppendLine("            " + invocation + ";");
            }
            else
            {
                output.AppendLine("            var resultValue = " + invocation + ";");
                WriteManagedResult(output, export.Method.ReturnType);
            }

            output.AppendLine("            return 0;");
            output.AppendLine("        }");
            output.AppendLine("        catch (Exception exception)");
            output.AppendLine("        {");
            output.AppendLine("            SetError(exception.ToString(), error);");
            output.AppendLine("            return 1;");
            output.AppendLine("        }");
        }

        private static void AddManagedInputParameters(List<string> output, string name, Type type)
        {
            if (type == typeof(string))
                output.Add("char* " + name);
            else if (type == typeof(double) || type == typeof(short) || type == typeof(int) || type == typeof(uint))
                output.Add(CSharpPrimitiveType(type) + " " + name);
            else if (type == typeof(bool))
                output.Add("int " + name);
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.Add(CSharpPrimitiveType(type.GetElementType()) + "* " + name + "Data");
                output.Add("int " + name + "Length");
            }
            else
            {
                output.Add(CSharpPrimitiveType(type.GetElementType()) + "* " + name + "Data");
                output.Add("int " + name + "Rows");
                output.Add("int " + name + "Columns");
            }
        }

        private static void AddManagedOutputParameters(List<string> output, Type type)
        {
            if (type == typeof(double) || type == typeof(short) || type == typeof(int) ||
                type == typeof(uint) || type == typeof(bool))
                output.Add(CSharpPrimitiveType(type) + "* result");
            else if (type == typeof(string))
                output.Add("char** result");
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.Add(CSharpPrimitiveType(type.GetElementType()) + "** result");
                output.Add("int* resultLength");
            }
            else
            {
                output.Add(CSharpPrimitiveType(type.GetElementType()) + "** result");
                output.Add("int* resultRows");
                output.Add("int* resultColumns");
            }
        }

        private static void WriteManagedInputConversion(StringBuilder output, string name, Type type, string indent)
        {
            if (type == typeof(string))
            {
                output.AppendLine(indent + "if (" + name + " == null) throw new ArgumentNullException(nameof(" + name + "));");
                output.AppendLine(indent + "var " + name + "Value = new string(" + name + ");");
            }
            else if (type == typeof(bool))
            {
                output.AppendLine(indent + "var " + name + "Value = " + name + " != 0;");
            }
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.AppendLine(indent + "if (" + name + "Length < 0 || (" + name + "Length != 0 && " + name + "Data == null)) throw new ArgumentOutOfRangeException(nameof(" + name + "Length));");
                output.AppendLine(indent + "var " + name + "Value = new " + CSharpType(type.GetElementType()) + "[" + name + "Length];");
                output.AppendLine(indent + "for (int i = 0; i < " + name + "Length; ++i) " + name + "Value[i] = " + name + "Data[i];");
            }
            else if (type == typeof(double[,]) || type == typeof(int[,]))
            {
                output.AppendLine(indent + "if (" + name + "Rows < 0 || " + name + "Columns < 0 || (" + name + "Rows != 0 && " + name + "Columns != 0 && " + name + "Data == null)) throw new ArgumentOutOfRangeException(nameof(" + name + "Rows));");
                output.AppendLine(indent + "var " + name + "Value = new " + CSharpType(type.GetElementType()) + "[" + name + "Rows, " + name + "Columns];");
                output.AppendLine(indent + "for (int row = 0; row < " + name + "Rows; ++row)");
                output.AppendLine(indent + "    for (int column = 0; column < " + name + "Columns; ++column)");
                output.AppendLine(indent + "        " + name + "Value[row, column] = " + name + "Data[row * " + name + "Columns + column];");
            }
            else if (type == typeof(double[][]) || type == typeof(int[][]))
            {
                output.AppendLine(indent + "if (" + name + "Rows < 0 || " + name + "Columns < 0 || (" + name + "Rows != 0 && " + name + "Columns != 0 && " + name + "Data == null)) throw new ArgumentOutOfRangeException(nameof(" + name + "Rows));");
                output.AppendLine(indent + "var " + name + "Value = new " + CSharpType(type.GetElementType().GetElementType()) + "[" + name + "Rows][];");
                output.AppendLine(indent + "for (int row = 0; row < " + name + "Rows; ++row)");
                output.AppendLine(indent + "{");
                output.AppendLine(indent + "    " + name + "Value[row] = new " + CSharpType(type.GetElementType().GetElementType()) + "[" + name + "Columns];");
                output.AppendLine(indent + "    for (int column = 0; column < " + name + "Columns; ++column)");
                output.AppendLine(indent + "        " + name + "Value[row][column] = " + name + "Data[row * " + name + "Columns + column];");
                output.AppendLine(indent + "}");
            }
            else
            {
                output.AppendLine(indent + "var " + name + "Value = " + name + ";");
            }
        }

        private static void WriteManagedResult(StringBuilder output, Type type)
        {
            if (type == typeof(bool))
            {
                output.AppendLine("            *result = resultValue ? 1 : 0;");
            }
            else if (ScalarTypes.Contains(type))
            {
                output.AppendLine("            *result = resultValue;");
            }
            else if (type == typeof(string))
            {
                output.AppendLine("            if (resultValue == null) throw new InvalidOperationException(\"The exported function returned a null string.\");");
                output.AppendLine("            char* buffer = (char*)NativeMemory.Alloc((nuint)(resultValue.Length + 1), (nuint)sizeof(char));");
                output.AppendLine("            if (buffer == null) throw new OutOfMemoryException();");
                output.AppendLine("            fixed (char* source = resultValue) Buffer.MemoryCopy(source, buffer, (long)(resultValue.Length + 1) * sizeof(char), (long)resultValue.Length * sizeof(char));");
                output.AppendLine("            buffer[resultValue.Length] = '\\0';");
                output.AppendLine("            *result = buffer;");
            }
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.AppendLine("            if (resultValue == null) throw new InvalidOperationException(\"The exported function returned an uninitialized array.\");");
                output.AppendLine("            *resultLength = resultValue.Length;");
                output.AppendLine("            " + CSharpPrimitiveType(type.GetElementType()) + "* buffer = resultValue.Length == 0 ? null : (" +
                                  CSharpPrimitiveType(type.GetElementType()) + "*)NativeMemory.Alloc((nuint)resultValue.Length, (nuint)sizeof(" +
                                  CSharpPrimitiveType(type.GetElementType()) + "));");
                output.AppendLine("            if (resultValue.Length != 0 && buffer == null) throw new OutOfMemoryException();");
                output.AppendLine("            for (int i = 0; i < resultValue.Length; ++i) buffer[i] = resultValue[i];");
                output.AppendLine("            *result = buffer;");
            }
            else
            {
                bool jagged = type == typeof(double[][]) || type == typeof(int[][]);
                string elementType = CSharpPrimitiveType(ArrayElementType(type));
                string rowsExpression = jagged ? "resultValue.Length" : "resultValue.GetLength(0)";
                output.AppendLine("            if (resultValue == null) throw new InvalidOperationException(\"The exported function returned an uninitialized matrix.\");");
                output.AppendLine("            int rows = " + rowsExpression + ";");
                if (jagged)
                {
                    output.AppendLine("            int columns = 0;");
                    output.AppendLine("            for (int row = 0; row < rows; ++row)");
                    output.AppendLine("            {");
                    output.AppendLine("                if (resultValue[row] == null) throw new InvalidOperationException(\"The exported function returned an uninitialized matrix row.\");");
                    output.AppendLine("                columns = Math.Max(columns, resultValue[row].Length);");
                    output.AppendLine("            }");
                }
                else
                {
                    output.AppendLine("            int columns = resultValue.GetLength(1);");
                }

                output.AppendLine("            *resultRows = rows;");
                output.AppendLine("            *resultColumns = columns;");
                output.AppendLine("            int count = checked(rows * columns);");
                output.AppendLine("            " + elementType + "* buffer = count == 0 ? null : (" + elementType +
                                  "*)NativeMemory.Alloc((nuint)count, (nuint)sizeof(" + elementType + "));");
                output.AppendLine("            if (count != 0 && buffer == null) throw new OutOfMemoryException();");
                output.AppendLine("            for (int row = 0; row < rows; ++row)");
                output.AppendLine("                for (int column = 0; column < columns; ++column)");
                output.AppendLine("                    buffer[row * columns + column] = " +
                                  (jagged ? "column < resultValue[row].Length ? resultValue[row][column] : default" : "resultValue[row, column]") + ";");
                output.AppendLine("            *result = buffer;");
            }
        }

        private static void WriteCppParameters(StringBuilder output, Export export)
        {
            ParameterInfo[] parameters = export.Method.GetParameters();
            for (int i = 0; i < parameters.Length; ++i)
            {
                output.Append(CppParameterType(export.NativeParameterTypes[i]) + " " + ArgumentName(i));
                if (i + 1 != parameters.Length) output.Append(", ");
            }
        }

        private static void WriteCppInputSetup(StringBuilder output, ParameterInfo parameter, Type type)
        {
            string name = ArgumentName(parameter.Position);
            if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.AppendLine("    std::vector<" + CppType(type.GetElementType()) + "> " + name + "Data;");
                output.AppendLine("    size_t " + name + "Length = ArrayTraits<MyArray>::size(" + name + ");");
                output.AppendLine("    " + name + "Data.reserve(" + name + "Length);");
                output.AppendLine("    for (size_t i = 0; i < " + name + "Length; ++i)");
                output.AppendLine("        " + name + "Data.push_back(static_cast<" + CppType(type.GetElementType()) +
                                  ">(ArrayTraits<MyArray>::getAt(" + name + ", i)));");
            }
            else if (type == typeof(double[,]) || type == typeof(int[,]) ||
                     type == typeof(double[][]) || type == typeof(int[][]))
            {
                output.AppendLine("    size_t " + name + "Rows = MatrixTraits<MyMatrix>::rows(" + name + ");");
                output.AppendLine("    size_t " + name + "Columns = MatrixTraits<MyMatrix>::columns(" + name + ");");
                output.AppendLine("    std::vector<" + CppType(ArrayElementType(type)) + "> " +
                                  name + "Data(" + name + "Rows * " + name + "Columns);");
                output.AppendLine("    for (size_t row = 0; row < " + name + "Rows; ++row)");
                output.AppendLine("        for (size_t column = 0; column < " + name + "Columns; ++column)");
                output.AppendLine("            " + name + "Data[row * " + name + "Columns + column] = static_cast<" +
                                  CppType(ArrayElementType(type)) + ">(MatrixTraits<MyMatrix>::getAt(" +
                                  name + ", row, column));");
            }
        }

        private static void WriteCppCall(StringBuilder output, Export export)
        {
            bool scalarResult = ScalarTypes.Contains(export.Method.ReturnType);
            string resultType = export.Method.ReturnType == typeof(bool) ? "int" : CppType(export.Method.ReturnType);
            output.AppendLine("    wchar_t* error = nullptr;");
            if (scalarResult)
                output.AppendLine("    " + resultType + " result{};");
            else if (export.Method.ReturnType == typeof(string))
                output.AppendLine("    wchar_t* result = nullptr;");
            else if (export.Method.ReturnType == typeof(double[]) || export.Method.ReturnType == typeof(int[]))
                output.AppendLine("    " + CppType(export.Method.ReturnType.GetElementType()) + "* result = nullptr;");
            else
                output.AppendLine("    " + CppType(ArrayElementType(export.Method.ReturnType)) + "* result = nullptr;");

            string outArguments;
            if (scalarResult || export.Method.ReturnType == typeof(string))
                outArguments = "&result";
            else if (export.Method.ReturnType == typeof(double[]) || export.Method.ReturnType == typeof(int[]))
                outArguments = "&result, &resultLength";
            else
                outArguments = "&result, &resultRows, &resultColumns";

            if (export.Method.ReturnType == typeof(double[]) || export.Method.ReturnType == typeof(int[]))
                output.AppendLine("    int resultLength = 0;");
            else if (export.Method.ReturnType == typeof(double[,]) || export.Method.ReturnType == typeof(int[,]) ||
                     export.Method.ReturnType == typeof(double[][]) || export.Method.ReturnType == typeof(int[][]))
                output.AppendLine("    int resultRows = 0, resultColumns = 0;");

            string arguments = string.Join(", ",
                export.Method.GetParameters().Select((p, index) =>
                    CppAotInputArgument(p, export.NativeParameterTypes[index]))
                    .Concat(new[] { outArguments, "&error" }));
            output.AppendLine("    int status = XlwAotCall_" + export.EntryPoint + "()(" + arguments + ");");
            output.AppendLine("    XlwCheckAotStatus(status, error);");
            if (!scalarResult)
                output.AppendLine("    std::unique_ptr<void, void (*)(void*)> resultOwner(result, &XlwAotFree);");
            if (scalarResult)
                output.AppendLine("    return " + (export.Method.ReturnType == typeof(bool) ? "result != 0" : "result") + ";");
            else if (export.Method.ReturnType == typeof(string))
            {
                output.AppendLine("    if (result == nullptr) throw std::runtime_error(\"The exported function returned a null string.\");");
                output.AppendLine("    std::wstring value(result);");
                output.AppendLine("    return value;");
            }
            else if (export.Method.ReturnType == typeof(double[]) || export.Method.ReturnType == typeof(int[]))
            {
                output.AppendLine("    MyArray value = ArrayTraits<MyArray>::create(static_cast<size_t>(resultLength));");
                output.AppendLine("    for (int i = 0; i < resultLength; ++i) ArrayTraits<MyArray>::setAt(value, static_cast<size_t>(i), static_cast<double>(result[i]));");
                output.AppendLine("    return value;");
            }
            else
            {
                output.AppendLine("    MyMatrix value = MatrixTraits<MyMatrix>::create(static_cast<size_t>(resultRows), static_cast<size_t>(resultColumns));");
                output.AppendLine("    for (int row = 0; row < resultRows; ++row)");
                output.AppendLine("        for (int column = 0; column < resultColumns; ++column)");
                output.AppendLine("            MatrixTraits<MyMatrix>::setAt(value, static_cast<size_t>(row), static_cast<size_t>(column), static_cast<double>(result[row * resultColumns + column]));");
                output.AppendLine("    return value;");
            }
        }

        private static string CppAotInputArgument(ParameterInfo parameter, Type type)
        {
            string name = ArgumentName(parameter.Position);
            if (type == typeof(string))
                return "reinterpret_cast<const char16_t*>(" + name + ".c_str())";
            if (type == typeof(bool))
                return name + " ? 1 : 0";
            if (type == typeof(double[]) || type == typeof(int[]))
                return name + "Data.empty() ? nullptr : " + name + "Data.data(), static_cast<int>(" + name + "Length)";
            if (type == typeof(double[,]) || type == typeof(int[,]) ||
                type == typeof(double[][]) || type == typeof(int[][]))
                return name + "Data.empty() ? nullptr : " + name + "Data.data(), static_cast<int>(" +
                       name + "Rows), static_cast<int>(" + name + "Columns)";
            return name;
        }

        private static string EntryPointDeclaration(Export export)
        {
            var parameters = new List<string>();
            ParameterInfo[] methodParameters = export.Method.GetParameters();
            for (int i = 0; i < methodParameters.Length; ++i)
                AddNativeParameterDeclarations(parameters, ArgumentName(i), export.NativeParameterTypes[i]);
            if (export.IsLifecycle)
            {
                parameters.Clear();
            }
            else
            {
                AddNativeOutputDeclarations(parameters, export.Method.ReturnType);
            }

            parameters.Add("wchar_t** error");
            return "extern \"C\" int __cdecl " + export.EntryPoint + "(" + string.Join(", ", parameters) + ")";
        }

        private static string EntryPointFunctionPointerDeclaration(Export export)
        {
            string declaration = EntryPointDeclaration(export);
            string parameters = declaration.Substring(declaration.IndexOf('('));
            return "using XlwAotFunction_" + export.EntryPoint + " = int (__cdecl *)" + parameters + ";";
        }

        private static void AddNativeParameterDeclarations(List<string> output, string name, Type type)
        {
            if (type == typeof(string))
                output.Add("const char16_t* " + name);
            else if (type == typeof(bool))
                output.Add("int " + name);
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.Add(CppType(type.GetElementType()) + "* " + name + "Data");
                output.Add("int " + name + "Length");
            }
            else if (type == typeof(double[,]) || type == typeof(int[,]) ||
                     type == typeof(double[][]) || type == typeof(int[][]))
            {
                output.Add(CppType(ArrayElementType(type)) + "* " + name + "Data");
                output.Add("int " + name + "Rows");
                output.Add("int " + name + "Columns");
            }
            else
                output.Add(CppType(type) + " " + name);
        }

        private static void AddNativeOutputDeclarations(List<string> output, Type type)
        {
            if (type == typeof(bool))
                output.Add("int* result");
            else if (type == typeof(double) || type == typeof(short) || type == typeof(int) || type == typeof(uint))
                output.Add(CppType(type) + "* result");
            else if (type == typeof(string))
                output.Add("wchar_t** result");
            else if (type == typeof(double[]) || type == typeof(int[]))
            {
                output.Add(CppType(type.GetElementType()) + "** result");
                output.Add("int* resultLength");
            }
            else
            {
                output.Add(CppType(ArrayElementType(type)) + "** result");
                output.Add("int* resultRows");
                output.Add("int* resultColumns");
            }
        }

        private static string CSharpType(Type type)
        {
            if (type == typeof(double)) return "double";
            if (type == typeof(int)) return "int";
            return type.FullName;
        }

        private static Type ArrayElementType(Type type)
        {
            Type elementType = type.GetElementType();
            return elementType.IsArray ? elementType.GetElementType() : elementType;
        }

        private static string CSharpPrimitiveType(Type type)
        {
            if (type == typeof(double)) return "double";
            if (type == typeof(short)) return "short";
            if (type == typeof(int)) return "int";
            if (type == typeof(uint)) return "uint";
            return "int";
        }

        private static string CppType(Type type)
        {
            if (type == typeof(double)) return "double";
            if (type == typeof(short)) return "short";
            if (type == typeof(int)) return "int";
            if (type == typeof(uint)) return "unsigned int";
            if (type == typeof(bool)) return "bool";
            if (type == typeof(string)) return "std::wstring";
            if (type == typeof(double[]) || type == typeof(int[])) return "MyArray";
            if (type == typeof(double[,]) || type == typeof(int[,]) ||
                type == typeof(double[][]) || type == typeof(int[][])) return "MyMatrix";
            throw new InvalidOperationException("Unsupported native XLW type: " + type.FullName);
        }

        private static string CppParameterType(Type type)
        {
            return ScalarTypes.Contains(type) ? CppType(type) : "const " + CppType(type) + "&";
        }

        private static Type GetNativeParameterType(Type type, IEnumerable<Conversion> conversions)
        {
            Conversion conversion = conversions.FirstOrDefault(c => c.Method.ReturnType == type);
            return conversion == null ? type : conversion.InputType;
        }

        private static bool IsCustomType(Type type, IEnumerable<Conversion> conversions)
        {
            return conversions.Any(c => c.Method.ReturnType == type);
        }

        private static bool IsNativeType(Type type)
        {
            return ScalarTypes.Contains(type) || type == typeof(string) || ArrayTypes.Contains(type);
        }

        private static bool IsSupportedExportType(Type type)
        {
            return type == typeof(void) || IsNativeType(type);
        }

        private static string MethodExpression(MethodInfo method)
        {
            string typeName = method.DeclaringType.FullName;
            if (typeName.Contains("`"))
                throw new InvalidOperationException("Generic declaring types are not supported for Native AOT exports.");
            return "global::" + typeName.Replace('+', '.');
        }

        private static string ConvertArgumentExpression(ParameterInfo parameter, IEnumerable<Conversion> conversions)
        {
            string valueName = ManagedValueName(parameter.Position);
            Conversion conversion = conversions.FirstOrDefault(c => c.Method.ReturnType == parameter.ParameterType);
            return conversion == null ? valueName :
                MethodExpression(conversion.Method) + "." + conversion.Method.Name + "(" + valueName + ")";
        }

        private static string ArgumentName(int index) => "arg" + index;

        private static string ManagedValueName(int index) => ArgumentName(index) + "Value";

        private static void ValidateCppIdentifier(string name)
        {
            if (!Regex.IsMatch(name, "^[A-Za-z_][A-Za-z0-9_]*$"))
                throw new InvalidOperationException("Exported method names must be valid C++ identifiers: " + name);
        }

    }
}
