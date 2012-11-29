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

using System;
using System.Collections.Generic;
using xlwDotNet;
using xlwDotNet.xlwTypes;

namespace TypeRegDemo
{
    public static class TypeConversions
    {
        [TypeRegister]
        public static List<double> ToListDouble(MyArray myArray)
        {
            var doubleList = new List<double>(myArray.size);
            for (int i = 0; i < myArray.size; ++i)
                doubleList.Add(myArray[i]);
            return doubleList;
        }

        [TypeRegister]
        public static Student ToStudent(CellMatrix cellMatrix)
        {
            if (cellMatrix.ColumnsInStructure != 1)
            {
                throw new Exception("Student must have 1 column");
            }
            if (cellMatrix.RowsInStructure != 2)
            {
                throw new Exception("Student must a name followed by an age");
            }
            if (!cellMatrix[0, 0].IsAString)
            {
                throw new Exception("Expected name of student in first cell");
            }
            if (!cellMatrix[1, 0].IsANumber)
            {
                throw new Exception ("Expected age of student in second cell");
            }
            return new Student(cellMatrix[0, 0].StringValue(), cellMatrix[1, 0].NumericValue());
        }
    }
}
