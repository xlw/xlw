/*
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/NCmatrices.h>
#include <algorithm>


// This will not leak. If the new throws it gets cleaned up and the
// NCMatrix is never created.
xlw::NCMatrix::NCMatrix(const NCMatrix& original):
         theData(original.theData.copy())
{}

xlw::NCMatrix::NCMatrix(size_t Rows_, size_t Columns_):
                        theData( new NCMatrixData(Rows_,Columns_))
{}


xlw::NCMatrix&
xlw::NCMatrix::resize(size_t rows, size_t columns)
{
    NCMatrix temp(rows,columns);
    swap(temp);
    return *this;

}



xlw::NCMatrix& xlw::NCMatrix::operator=(const NCMatrix& original)
{
    if (this != &original)
    {
       NCMatrix temp(original);
       swap(temp);

    }

    return *this;
}


