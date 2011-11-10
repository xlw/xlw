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
using System.Text;
using System.Reflection;
using IO = System.IO;
using xlwDotNet;

namespace DotNetInterfaceGenerator
{
    public static class Program
    {
        static List<Type> primitives = new List<Type>();
        static List<Type> semiprimitives = new List<Type>();
        static List<Type> xlwTypes = new List<Type>();
        static List<Type> customTypes = new List<Type>();
        static List<Type> customInputTypes = new List<Type>();
        static List<String> customConversionMethodNames = new List<String>();

        static Program()
        {
            primitives.Add(typeof(double));
            primitives.Add(typeof(short));
            primitives.Add(typeof(int));
            primitives.Add(typeof(UInt32));
            primitives.Add(typeof(Boolean));
            semiprimitives.Add(typeof(string));
            semiprimitives.Add(typeof(double[]));
            semiprimitives.Add(typeof(double[,]));
            Assembly xlwAssembly = Assembly.GetAssembly(typeof(ExcelExportAttribute));
            Type[] xlwCandidateTypes = xlwAssembly.GetExportedTypes();
            foreach (Type t in xlwCandidateTypes)
                if (t.Namespace == "xlwDotNet.xlwTypes") xlwTypes.Add(t);
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
                {
                    dirName = args[2];
                }

                string fileName = args[1];
                if (args.Length == 4)
                {
                    fileName = args[3];
                }

                IO.Directory.CreateDirectory(dirName);
                IO.StreamWriter headerFile = IO.File.CreateText(dirName + "/" + fileName + ".h");
                IO.StreamWriter sourceFile = IO.File.CreateText(dirName + "/" + fileName + ".cpp");
                AssemblyFinderGenerator.WriteAssemblyFinder(dirName + "/" + "AssembleyFinder.cpp");

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
                        TypeRegisterAttribute[] typeConversionAttributeArray =
                            (TypeRegisterAttribute[])method.GetCustomAttributes(typeof(TypeRegisterAttribute), false);
                        if (typeConversionAttributeArray.Length == 0) continue;

                        if (!method.IsStatic || !method.IsPublic)
                            throw new Exception ("Type conversions should be public static methods");

                        Type customType = method.ReturnType;
                        if (primitives.Contains(customType) || semiprimitives.Contains(customType) || xlwTypes.Contains(customType))
                            throw new Exception("Type conversion method " + method.Name + " not permitted: The custom type " + customType + " is already a valid xlw input type");

                        ParameterInfo[] paramInfos = method.GetParameters();
                        if (paramInfos.Length != 1)
                            throw new Exception("Type conversion method " + method.Name + " should have exactly one parameter");
                        Type customInputType = paramInfos[0].ParameterType;
                        if (!primitives.Contains(customInputType) && !semiprimitives.Contains(customInputType) && !xlwTypes.Contains(customInputType))
                            throw new Exception("Type conversion method " + method.Name + " not permitted: The input type " + customInputType + " should be a valid xlw type");

                        customConversionMethodNames.Add(cppify(method.DeclaringType.FullName + "." + method.Name));
                        customTypes.Add(customType);
                        customInputTypes.Add(customInputType);
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
                        if (excelExportAttributeArray.Length > 1) throw new Exception("Method must have exactly one ExcelExportAttribute");
                        ExcelExportAttribute excelExportAttribute = excelExportAttributeArray[0];

                        if (!primitives.Contains(method.ReturnType) &&
                            !semiprimitives.Contains(method.ReturnType) &&
                            !xlwTypes.Contains(method.ReturnType))
                            throw new Exception("Not exporting  " + method.Name + ": Unknown return type");

                        string basicReturnType = writeCType(method.ReturnType, false, true);
                        headerFile.WriteLine(basicReturnType + " // " + excelExportAttribute.Description);
                        sourceFile.WriteLine(basicReturnType + " // " + excelExportAttribute.Description);

                        if (excelExportAttribute.volatileFlag)   headerFile.WriteLine("//<xlw:volatile");
                        if (excelExportAttribute.timeFlag)       headerFile.WriteLine("//<xlw:time");
                        if (excelExportAttribute.threadSafeFlag) headerFile.WriteLine("//<xlw:threadsafe");
                        if (excelExportAttribute.xlmCommandFlag) headerFile.WriteLine("//<xlw:macrosheet");

                        headerFile.Write(writeCMethod(method.Name) + "(");
                        sourceFile.Write("DLLEXPORT " + writeCMethod(method.Name) + "(");
                        int i = 1;
                        ParameterInfo[] paramInfo = method.GetParameters();
                        foreach (ParameterInfo param in paramInfo)
                        {
                            ParameterAttribute[] ParameterAttributeArray =
                                    (ParameterAttribute[])param.GetCustomAttributes(typeof(ParameterAttribute), false);
                            if (ParameterAttributeArray.Length != 1)
                                throw new Exception("Method Parameters must have exactly one ParameterAttribute");

                            Type parameterType = param.ParameterType;
                            if (customTypes.Contains(parameterType))
                                parameterType = customInputTypes[customTypes.IndexOf(parameterType)]; // substitute the parameterType for its custom conversion

                            string CType = writeCType(parameterType, true);
                            headerFile.Write(CType + param.Name);
                            sourceFile.Write(CType + param.Name);
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
                        writeFunctionBody(sourceFile, method);
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
        static string writeCType(Type CSType, bool constRef)
        {
            return writeCType(CSType, constRef, false);
        }

        static string writeCType(Type CSType, bool constRef, bool returnType) // returnType is unused at the moment
        {
            string[] tokens = CSType.Name.Split('.');
            string basicType = tokens[tokens.Length - 1];

            if (primitives.Contains(CSType))
            {
                basicType = basicType.ToLower();
                if (basicType == "int32")
                    basicType = "int";
                if (basicType == "int16")
                    basicType = "short";
                if (basicType == "uint32")
                    basicType = "unsigned long";
                if (basicType == "boolean")
                    basicType = "bool";
                return basicType; // no need for "const & " qualifier
            }
            else if (semiprimitives.Contains(CSType))
            {
                basicType = basicType.ToLower();
                if (basicType == "string")
                    basicType = "std::wstring";
                if (basicType == "double[]")
                    basicType = "MyArray";
                if (basicType == "double[,]")
                    basicType = "MyMatrix";
            }
            else if (returnType && customTypes.Contains(CSType))
                throw new Exception("Exported function cannot return a custom type");

            if (constRef) return "const " + basicType + "& ";

            return basicType;
        }

        static string writeCMethod(string CSName)
        {
            string[] tokens = CSName.Split('.');
            return tokens[tokens.Length - 1];

        }

        static void writeFunctionBody(IO.StreamWriter sourceFile, MethodInfo theMethod)
        {

            sourceFile.WriteLine("{");
            sourceFile.WriteLine("DOT_NET_EXCEL_BEGIN");

            string castString = "";

            if (!primitives.Contains(theMethod.ReturnType))
                castString = "*(" + writeCType(theMethod.ReturnType, false) +
                             "*)(xlwTypes::" + writeCType(theMethod.ReturnType, false) + "::getInner(";

            if (theMethod.ReturnType == typeof(String))
                castString = "(CLR2WCPP(";

            string tabString = "        ";
            sourceFile.WriteLine(tabString + "return " + castString + cppify(theMethod.DeclaringType.FullName + "." + theMethod.Name) + "(");

            ParameterInfo[] paramInfo = theMethod.GetParameters();
            int i = 1;
            foreach (ParameterInfo param in paramInfo)
            {
                sourceFile.Write(tabString + tabString);
                Type parameterType = param.ParameterType;
                bool isCustomType = false;
                if (customTypes.Contains(parameterType))
                {
                    int j = customTypes.IndexOf(parameterType);
                    parameterType = customInputTypes[j]; // substitute the parameterType for its custom conversion
                    isCustomType = true;
                    sourceFile.Write(customConversionMethodNames[j] + "(");
                }

                /////// Primitive Type
                if (primitives.Contains(parameterType))
                    sourceFile.Write(param.Name);
                else
                {
                    /////// A String
                    if (param.ParameterType == typeof(String))
                        sourceFile.Write("gcnew String(" + param.Name + ".c_str())");
                    else
                        sourceFile.Write("gcnew xlwTypes::" + writeCType(parameterType, false) + "(IntPtr((void*)&" + param.Name + "))");
                }

                if (isCustomType)
                    sourceFile.Write(")");
                if (i != paramInfo.Length)
                    sourceFile.Write(",");
                i++;
                sourceFile.WriteLine();
            }
            sourceFile.Write(tabString + ")");

            if (!primitives.Contains(theMethod.ReturnType))
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

