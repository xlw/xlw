/*
 Copyright (C) 2011 Mark P Owen

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

using System.Collections.Generic;
using System.Linq;
using xlwDotNet;

namespace TypeRegDemo
{
    public class Class1
    {
        [ExcelExport("Adds all the elements of the list")]
        public static double SumVector([Parameter("List of values")] List<double> v)
        {
            return v.Sum();
        }

        [ExcelExport("Gets the student's exam result")]
        public static double ExamResult ([Parameter("The student")] Student student)
        {
            return student.ExamResult;
        }
    }
}

