/*
 Copyright (C) 2006 Mark Joshi


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#include <xlw/xlarray.h>

xlw::NEMatrix xlw::GetMatrix(LPXLARRAY input)
{
    int rows = input->rows;
    int cols = input->columns;

    NEMatrix result(rows,cols);
    for (int i=0; i < rows; ++i)
        for (int j=0; j < cols; ++j)
        {
            int k = i*cols+j;
            double val = input->data[k];
            result(i,j)= val;
        }
    return result;
}
