/*
 Copyright (C) 2008 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Mark P Owen

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

using System;
using System.Collections.Generic;
using System.Reflection;
using IO = System.IO;
using xlwDotNet;

namespace DotNetInterfaceGenerator
{
    public static class Program
    {
        private static readonly List<Type> Primitives = new List<Type>();
        private static readonly List<Type> Semiprimitives = new List<Type>();
        private static readonly List<Type> XLWTypes = new List<Type>();
        private static readonly List<Type> CustomTypes = new List<Type>();
        private static readonly List<Type> CustomInputTypes = new List<Type>();
        private static readonly List<String> CustomConversionMethodNames = new List<String>();

        static Program()
        {
            Primitives.Add(typeof(double));
            Primitives.Add(typeof(short));
            Primitives.Add(typeof(int));
            Primitives.Add(typeof(UInt32));
            Primitives.Add(typeof(Boolean));
            Semiprimitives.Add(typeof(string));
            Semiprimitives.Add(typeof(double[]));
            Semiprimitives.Add(typeof(double[,]));
            Semiprimitives.Add(typeof(double[][]));
            Semiprimitives.Add(typeof(int[]));
            Semiprimitives.Add(typeof(int[,]));
            Semiprimitives.Add(typeof(int[][]));
            Assembly xlwAssembly = Assembly.GetAssembly(typeof(ExcelExportAttribute));
            Type[] xlwCandidateTypes = xlwAssembly.GetExportedTypes();
            foreach (Type t in xlwCandidateTypes)
                if (t.Namespace == "xlwDotNet.xlwTypes")
                    XLWTypes.Add(t);
        }

        static int Main(string[] args)
        {
            try
            {
                if (args.Length > 4 || args.Length < 2)
                {
                    Console.WriteLine("Usage: DotNetInterfaceGenerator <input assembly> <output library name> <output directory> <outputfilename>");
                    return 0;
                }
                Assembly sourceAssembly = Assembly.LoadFrom(args[0]);
                Type[] sourceTypes = sourceAssembly.GetExportedTypes();

                string dirName = "";
                if (args.Length >= 3)
                    dirName = args[2];

                string fileName = args[1];
                if (args.Length == 4)
                    fileName = args[3];

                IO.Directory.CreateDirectory(dirName);
                IO.StreamWriter headerFile = IO.File.CreateText(dirName + "/" + fileName + ".h");
                IO.StreamWriter sourceFile = IO.File.CreateText(dirName + "/" + fileName + ".cpp");
                AssemblyFinderGenerator.WriteAssemblyFinder(dirName + "/" + "AssemblyFinder.cpp");

                headerFile.WriteLine("#ifndef " + fileName.ToUpper() + "_H");
                headerFile.WriteLine("#define " + fileName.ToUpper() + "_H"); headerFile.WriteLine();
                headerFile.WriteLine("#define ERRCELLS_NOT_REQUIRED"); headerFile.WriteLine();
                headerFile.WriteLine("#include <xlwDotNet.h>"); headerFile.WriteLine();
                headerFile.WriteLine("//<xlw:libraryname=" + args[1]); headerFile.WriteLine();

                //sourceFile.WriteLine("#pragma warning (disable : 4996)"); sourceFile.WriteLine();

                sourceFile.WriteLine("#include <xlwDotNet.h>"); headerFile.WriteLine();

                //sourceFile.WriteLine("using namespace " + args[1] + ";");
                sourceFile.WriteLine("using namespace System;");
                sourceFile.WriteLine("using namespace Runtime::InteropServices;");
                sourceFile.WriteLine("using namespace xlwDotNet;"); sourceFile.WriteLine();

                sourceFile.WriteLine("inline std::wstring CLR2WCPP(String^ clrString) {");
                sourceFile.WriteLine("    System::IntPtr memHandle = Marshal::StringToHGlobalUni(clrString);");
                sourceFile.WriteLine("    std::wstring result =  (const wchar_t*)(memHandle.ToPointer());");
                sourceFile.WriteLine("    Marshal::FreeHGlobal(memHandle);");
                sourceFile.WriteLine("    return result;");
                sourceFile.WriteLine("}"); sourceFile.WriteLine();

                foreach (Type t in sourceTypes) // search for public static type conversion methods identified by a TypeConversionAttribute
                {
                    MethodInfo[] classMethods = t.GetMethods();
                    foreach (MethodInfo method in classMethods)
                    {
                        TypeRegisterAttribute[] typeConversionAttributeArray = (TypeRegisterAttribute[]) method.GetCustomAttributes(typeof (TypeRegisterAttribute), false);
                        if (typeConversionAttributeArray.Length == 0) continue;
                        if (!method.IsStatic || !method.IsPublic)
                            throw new Exception("Type conversions should be public static methods");

                        Type customType = method.ReturnType;
                        if (Primitives.Contains(customType) || Semiprimitives.Contains(customType) || XLWTypes.Contains(customType))
                            throw new Exception("Type conversion method " + method.Name + " not permitted: The custom type " + customType + " is already a valid xlw input type");

                        ParameterInfo[] paramInfos = method.GetParameters();
                        if (paramInfos.Length != 1)
                            throw new Exception("Type conversion method " + method.Name + " should have exactly one parameter");
                        Type customInputType = paramInfos[0].ParameterType;
                        if (!Primitives.Contains(customInputType) && !Semiprimitives.Contains(customInputType) && !XLWTypes.Contains(customInputType))
                            throw new Exception("Type conversion method " + method.Name + " not permitted: The input type " + customInputType + " should be a valid xlw type");

                        CustomConversionMethodNames.Add(cppify(method.DeclaringType.FullName + "." + method.Name));
                        CustomTypes.Add(customType);
                        CustomInputTypes.Add(customInputType);
                    }
                }

                foreach (Type t in sourceTypes) // search for public static methods exported using an ExcelExportAttribute
                {
                    MethodInfo[] classMethods = t.GetMethods();
                    foreach (MethodInfo method in classMethods)
                    {
                        if (!method.IsStatic || !method.IsPublic) continue;

                        ExcelExportAttribute[] excelExportAttributeArray = (ExcelExportAttribute[])method.GetCustomAttributes(typeof(ExcelExportAttribute), false);

                        if (excelExportAttributeArray.Length == 0) continue;
                        if (excelExportAttributeArray.Length > 1)
                            throw new Exception("Method must have exactly one ExcelExportAttribute");
                        ExcelExportAttribute excelExportAttribute = excelExportAttributeArray[0];

                        if (!Primitives.Contains(method.ReturnType) &&
                            !Semiprimitives.Contains(method.ReturnType) &&
                            !XLWTypes.Contains(method.ReturnType))
                            throw new Exception("Not exporting  " + method.Name + ": Unknown return type");

                        string basicReturnType = WriteCType(method.ReturnType, false, true);
                        headerFile.WriteLine(basicReturnType + " // " + excelExportAttribute.Description);
                        sourceFile.WriteLine(basicReturnType + " // " + excelExportAttribute.Description);

                        if (excelExportAttribute.volatileFlag)   headerFile.WriteLine("//<xlw:volatile");
                        if (excelExportAttribute.timeFlag)       headerFile.WriteLine("//<xlw:time");
                        if (excelExportAttribute.threadSafeFlag) headerFile.WriteLine("//<xlw:threadsafe");
                        if (excelExportAttribute.xlmCommandFlag) headerFile.WriteLine("//<xlw:macrosheet");

                        headerFile.Write(WriteCMethod(method.Name) + "(");
                        sourceFile.Write("DLLEXPORT " + WriteCMethod(method.Name) + "(");
                        int i = 1;
                        ParameterInfo[] paramInfo = method.GetParameters();
                        foreach (ParameterInfo param in paramInfo)
                        {
                            ParameterAttribute[] ParameterAttributeArray =
                                    (ParameterAttribute[])param.GetCustomAttributes(typeof(ParameterAttribute), false);
                            if (ParameterAttributeArray.Length != 1)
                                throw new Exception("Method Parameters must have exactly one ParameterAttribute");

                            Type parameterType = param.ParameterType;
                            if (CustomTypes.Contains(parameterType))
                                parameterType = CustomInputTypes[CustomTypes.IndexOf(parameterType)]; // substitute the parameterType for its custom conversion

                            string cType = WriteCType(parameterType, true);
                            headerFile.Write(cType + " " + param.Name);
                            sourceFile.Write(cType + " " + param.Name);
                            if (i != paramInfo.Length)
                            {
                                headerFile.Write(",");
                                sourceFile.Write(",");
                            }
                            ++i;
                            headerFile.WriteLine(" // " + ParameterAttributeArray[0].Description);
                        }
                        headerFile.WriteLine(");");
                        headerFile.WriteLine();
                        sourceFile.WriteLine(")");
                        WriteFunctionBody(sourceFile, method);
                        sourceFile.WriteLine();
                    }
                }
                headerFile.WriteLine("#endif ");
                headerFile.Close();
                sourceFile.Close();
                return 0;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return -1;
            }
        }

        static string WriteCType(Type csType, bool constRef)
        {
            return WriteCType(csType, constRef, false);
        }

        static string WriteCType(Type csType, bool constRef, bool returnType)
        {
            string[] tokens = csType.Name.Split('.');
            string basicType = tokens[tokens.Length - 1];

            if (Primitives.Contains(csType))
            {
                basicType = basicType.ToLower();

                if (basicType == "int32")   basicType = "int";
                if (basicType == "int16")   basicType = "short";
                if (basicType == "uint32")  basicType = "unsigned long";
                if (basicType == "boolean") basicType = "bool";

                return basicType; // no need for "const & " qualifier
            }
            else if (Semiprimitives.Contains(csType))
            {
                basicType = basicType.ToLower();

                if (basicType == "string")      basicType = "std::wstring";
                if (basicType == "double[]")    basicType = "MyArray";
                if (basicType == "double[,]")   basicType = "MyMatrix";
                if (basicType == "double[][]")  basicType = "MyMatrix";
                if (basicType == "int[]")       basicType = "MyArray";
                if (basicType == "int[,]")      basicType = "MyMatrix";
                if (basicType == "int[][]")     basicType = "MyMatrix";
            }
            else if (returnType && CustomTypes.Contains(csType))
                throw new Exception("Exported function cannot return a custom type");

            if (constRef) return "const " + basicType + "&";

            return basicType;
        }

        static string WriteCMethod(string csName)
        {
            string[] tokens = csName.Split('.');
            return tokens[tokens.Length - 1];

        }

        static void WriteFunctionBody(IO.StreamWriter sourceFile, MethodInfo theMethod)
        {

            sourceFile.WriteLine("{");
            sourceFile.WriteLine("DOT_NET_EXCEL_BEGIN");

            string castString = "";

            if (!Primitives.Contains(theMethod.ReturnType))
                castString = "*(" + WriteCType(theMethod.ReturnType, false) +
                             "*)(xlwTypes::" + WriteCType(theMethod.ReturnType, false) + "::getInner(";

            if (theMethod.ReturnType == typeof(String))
                castString = "(CLR2WCPP(";

            const string tabString = "        ";
            sourceFile.WriteLine(tabString + "return " + castString + cppify(theMethod.DeclaringType.FullName + "." + theMethod.Name) + "(");

            ParameterInfo[] paramInfo = theMethod.GetParameters();
            for (int index = 0; index < paramInfo.Length; ++index)
            {
                ParameterInfo param = paramInfo[index];
                sourceFile.Write(tabString + tabString);
                Type parameterType = param.ParameterType;
                bool isCustomType = false;
                if (CustomTypes.Contains(parameterType))
                {
                    int j = CustomTypes.IndexOf(parameterType);
                    parameterType = CustomInputTypes[j]; // substitute the parameterType for its custom conversion
                    isCustomType = true;
                    sourceFile.Write(CustomConversionMethodNames[j] + "(");
                }

                /////// Primitive Type
                if (Primitives.Contains(parameterType))
                    sourceFile.Write(param.Name);
                else
                {
                    /////// A String
                    if (param.ParameterType == typeof (String))
                        sourceFile.Write("gcnew String(" + param.Name + ".c_str())");
                    else
                        sourceFile.Write("gcnew xlwTypes::" + WriteCType(parameterType, false) + "(IntPtr((void*)& " + param.Name + "))");
                }

                if (isCustomType) sourceFile.Write(")");
                if (index + 1 != paramInfo.Length) sourceFile.Write(",");
                sourceFile.WriteLine();
            }
            sourceFile.Write(tabString + ")");

            if (!Primitives.Contains(theMethod.ReturnType))
                sourceFile.Write("))");

            sourceFile.WriteLine(";");
            sourceFile.WriteLine("DOT_NET_EXCEL_END");

            sourceFile.WriteLine("}");
        }

        static string cppify(string theSource)
        {
            return theSource.Replace(".", "::");
        }

    }
}

