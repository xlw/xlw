/*
 Copyright (C) 2008 2009  Narinder S Claire

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
using xlwDotNet;
using xlwDotNet.xlwTypes;
using IronPython;
using IronPython.Hosting;
using Microsoft.Scripting;
using Microsoft.Scripting.Hosting;


namespace Example
{
    public class Class1
    {
        private static ScriptEngine engine;
        private static ScriptScope scope;

        static Class1()
        {
            engine = IronPython.Hosting.Python.CreateEngine();
            scope = engine.CreateScope();

        }

        public class CellFactory
        {
            public CellValue Cell(string s) { return new CellValue(s); }
            public CellValue Cell(double x) { return new CellValue(x); }
            public CellValue Cell(int i) { return new CellValue(i); }
            public CellValue Cell(CellValue o) { return new CellValue(o); }
            public CellMatrix Range(int i, int j) { return new CellMatrix(i, j); }
            public CellMatrix Range(CellMatrix o) { return new CellMatrix(0); }
        }

        [ExcelExport("Calls a Python function ")]
        public static CellMatrix Python(
                        [Parameter("The Python Code")] CellMatrix PythonCode,
                        [Parameter("The Parameters ")] CellMatrix TheParameters
                            )
        {

            if (PythonCode.ColumnsInStructure != 1)
            {
                throw new Exception("The Python code should  be one column of strings");
            }
            string theCode = "";
            for (int i = 0; i < PythonCode.RowsInStructure; ++i)
            {
                if (!PythonCode[i, 0].IsEmpty)
                {
                    theCode = theCode + PythonCode[i, 0].StringValue() + "\n";
                }
            }
            CellFactory theFactory = new CellFactory();
            scope.SetVariable("Input", TheParameters);
            scope.SetVariable("CellFactory", theFactory);
            ScriptSource source = engine.CreateScriptSourceFromString(theCode, SourceCodeKind.Statements);
            source.Execute(scope);
            return (CellMatrix)scope.GetVariable("Output");
  
        }

    }
}


