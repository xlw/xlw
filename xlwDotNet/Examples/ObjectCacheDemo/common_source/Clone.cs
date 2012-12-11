
/*
 Copyright (C) 2012  Narinder S Claire

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


using xlwDotNet.xlwTypes;

namespace xlwObjectCachDemo
{
    public static class CloneClass
    {

        public static CellMatrix Clone(this CellMatrix theMatrix)
        {
            CellMatrix theClone = new CellMatrix(theMatrix.RowsInStructure, theMatrix.ColumnsInStructure);
            for (int i = 0; i < theMatrix.RowsInStructure; ++i)
            {
                for (int j = 0; j < theMatrix.ColumnsInStructure; ++j)
                {
                    theClone[i, j] = new CellValue(theMatrix[i, j]);
                }
            }

            return theClone;
        }

        public static MyMatrix Clone(this MyMatrix theMatrix)
        {
            MyMatrix theClone = new MyMatrix(theMatrix.rows, theMatrix.columns);
            for (int i = 0; i < theMatrix.rows; ++i)
            {
                for (int j = 0; j < theMatrix.columns; ++j)
                {
                    theClone[i, j] = theMatrix[i, j];
                }
            }

            return theClone;
        }
    }
}
