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
    public class Program
    {
        static List<Type> primitives = new List<Type>();
        static List<Type> semiprimitives = new List<Type>();
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
                Assembly xlwAssembly = Assembly.GetAssembly(typeof(ExcelExportAttribute));
                Type[] sourceTypes = sourceAssembly.GetExportedTypes();
                Type[] xlwCandidateTypes = xlwAssembly.GetExportedTypes();
                List<Type> xlwTypes = new List<Type>();
                foreach (Type t in xlwCandidateTypes)
                {
                    if (t.Namespace == "xlwDotNet.xlwTypes") xlwTypes.Add(t);
                }


                string dirName = "";
                if (args.Length >= 3)
                {
                    dirName = args[2];
                }

                string fileName=args[1];
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

               // sourceFile.WriteLine("using namespace " + args[1] + ";");
                sourceFile.WriteLine("using namespace System;");
                sourceFile.WriteLine("using namespace Runtime::InteropServices;");
                sourceFile.WriteLine("using namespace xlwDotNet;"); sourceFile.WriteLine();

                sourceFile.WriteLine("inline std::wstring CLR2WCPP(String^ clrString) {");
                sourceFile.WriteLine("    System::IntPtr memHandle = Marshal::StringToHGlobalUni(clrString);");
                sourceFile.WriteLine("    std::wstring result =  (const wchar_t*)(memHandle.ToPointer());");
                sourceFile.WriteLine("    Marshal::FreeHGlobal(memHandle);");
                sourceFile.WriteLine("    return result;");
                sourceFile.WriteLine("}"); sourceFile.WriteLine();

                foreach (Type t in sourceTypes)
                {
                    MethodInfo[] classMethods = t.GetMethods();
                    foreach (MethodInfo method in classMethods)
                    {
                        if (!method.IsStatic || !method.IsPublic)
                            continue;

                        object[] attributes = method.GetCustomAttributes(false);
                        bool isExcel = false;
                        foreach (object att in attributes) isExcel = (isExcel | (att is ExcelExportAttribute));
                        if (!isExcel)
                            continue;

                        ParameterInfo[] paramInfo = method.GetParameters();
                        bool isParamOk = true;
                        foreach (ParameterInfo param in paramInfo)
                        {
                            isParamOk =
                                isParamOk && ((xlwTypes.Contains(method.ReturnType)) || (primitives.Contains(method.ReturnType)) || (semiprimitives.Contains(method.ReturnType)));
                        }
                        isParamOk =
                                isParamOk && ((xlwTypes.Contains(method.ReturnType)) || (primitives.Contains(method.ReturnType)) || (semiprimitives.Contains(method.ReturnType)));
                        if (!isParamOk)
                        {
                            throw(new Exception("Not exporting  " + method.Name + " : Unknown Parameter"));
                        }
                        else
                        {
                            string basicReturnType = writeCType(method.ReturnType,false,true);
                            ExcelExportAttribute[] ExcelExportAttributeArray =
                                        (ExcelExportAttribute[])method.GetCustomAttributes(typeof(ExcelExportAttribute), false);
                            if (ExcelExportAttributeArray.Length != 1) throw new Exception("Method must have exactly one ExcelExportAttribute");

                            headerFile.WriteLine(basicReturnType + " //" + ExcelExportAttributeArray[0].Description);
                            sourceFile.WriteLine(basicReturnType + " //" + ExcelExportAttributeArray[0].Description);

                            if (ExcelExportAttributeArray[0].volatileFlag)
                            {
                                headerFile.WriteLine("//<xlw:volatile");
                            }

                            if (ExcelExportAttributeArray[0].timeFlag)
                            {
                                headerFile.WriteLine("//<xlw:time");
                            }

                            if (ExcelExportAttributeArray[0].threadSafeFlag)
                            {
                                headerFile.WriteLine("//<xlw:threadsafe");
                            }

                            if (ExcelExportAttributeArray[0].xlmCommandFlag)
                            {
                                headerFile.WriteLine("//<xlw:macrosheet");
                            }


                            headerFile.Write(writeCMethod(method.Name) + "(");
                            sourceFile.Write(" DLLEXPORT "+writeCMethod(method.Name) + "(");
                            int i = 1;
                            foreach (ParameterInfo param in paramInfo)
                            {
                                ParameterAttribute[] ParameterAttributeArray =
                                        (ParameterAttribute[])param.GetCustomAttributes(typeof(ParameterAttribute), false);
                                if (ParameterAttributeArray.Length != 1) throw new Exception("Method Parameters must have exactly one  ParameterAttribute");
                                headerFile.Write(writeCType(param.ParameterType,true) +
                                                        " " + param.Name);
                                sourceFile.Write(writeCType(param.ParameterType,true) +
                                                        " " + param.Name);
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

                        }
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

        static string writeCType(Type CSType,bool constRef,bool returnType)
        {
            string[] tokens = CSType.Name.Split('.');
            string basicType = tokens[tokens.Length - 1];
            if(primitives.Contains(CSType))
            {
                basicType = basicType.ToLower();
                if (basicType == "int32")
                {
                    basicType = "int";
                }
                if (basicType == "int16")
                {
                    basicType = "short";
                }
                if (basicType == "uint32")
                {
                    basicType = "unsigned long";
                }
                if (basicType == "boolean")
                {
                    basicType = "bool";
                }
                return basicType;
            }
            if(semiprimitives.Contains(CSType))
            {
                basicType = basicType.ToLower();
                if (basicType == "string") basicType = "std::wstring";
                if (basicType == "double[]")basicType = "MyArray";
                if (basicType == "double[,]") basicType = "MyMatrix";
            }
            if(constRef) return "const " + basicType +"& ";
            return basicType ;
        }

        static string writeCMethod(string CSName)
        {
            string[] tokens = CSName.Split('.');
            return tokens[tokens.Length - 1];
           
        }

        static void writeFunctionBody(IO.StreamWriter sourceFile, MethodInfo theMethod)
        {
             ParameterInfo[] paramInfo = theMethod.GetParameters();
             string tabString = "        ";

             sourceFile.WriteLine("{");
             sourceFile.WriteLine("DOT_NET_EXCEL_BEGIN ");

             string castString = "";

             if (!primitives.Contains(theMethod.ReturnType))
             {
                 castString = "*(" + writeCType(theMethod.ReturnType, false) +
                              "*)(xlwTypes::"+ writeCType(theMethod.ReturnType, false)+ "::getInner(" ;

             }
             if (theMethod.ReturnType == typeof(String))
             {
                 castString = "(CLR2WCPP(";
                 
             }

             
             sourceFile.WriteLine(tabString + "return " + castString + cppify(theMethod.DeclaringType.FullName) + "::" + theMethod.Name + "(");
        
             int i = 1;
             foreach (ParameterInfo param in paramInfo)
             {
                 ParameterAttribute theAttribute =
                                               (ParameterAttribute)param.GetCustomAttributes(typeof(ParameterAttribute), false)[0];
                 
                 
                 /////// Primitive Type
                 if (primitives.Contains(param.ParameterType))
                 {
                     sourceFile.Write(tabString + tabString + param.Name);
                 }

                 else
                 {
                     /////// A String
                     if (param.ParameterType == typeof(String))
                         sourceFile.Write(tabString + tabString + "gcnew String(" + param.Name + ".c_str())");
                     else
                         sourceFile.Write(tabString + tabString + "gcnew xlwTypes::" + writeCType(param.ParameterType, false) + "(IntPtr((void*)&" + param.Name + "))");
                 }
              
                 if (i != paramInfo.Length)
                  {
                         sourceFile.Write(",");
                  }
                 i++;
                 sourceFile.WriteLine();
             }
             sourceFile.Write(tabString + ")");
             if (!primitives.Contains(theMethod.ReturnType))
             {
                 sourceFile.Write("))");
             }
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

