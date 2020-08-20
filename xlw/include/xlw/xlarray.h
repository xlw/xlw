/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2011 John Adcock
 Copyright (C) 2020 Narinder S Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - https://xlw.github.io/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef XL_ARRAY_H
#define XL_ARRAY_H

#include "xlcall32.h"
#include "xlw/MyContainers.h"
#include <xlw/xlfExcel.h>
#include <xlw/TempMemory.h>

namespace xlw {

  

    typedef FP12* LPXLARRAY;

    //! convert an incoming excel array into our matrix type
    inline NEMatrix GetMatrix(LPXLARRAY input)
    {
        size_t rows;
        size_t cols;
        double* values;

        rows = input->rows;
        cols = input->columns;
        values = input->array;


        NEMatrix result(MatrixTraits<NEMatrix>::create(rows, cols));
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                size_t k = i * cols + j;
                double val = values[k];
                MatrixTraits<NEMatrix>::setAt(result, i, j, val);
            }
        }
        return result;
    }

    inline void extractArrayInfo(const LPXLARRAY input, int& rows, int& cols, double*& arrayData)
    {

        rows = input->rows;
        cols = input->columns;
        arrayData = input->array;

    }

    inline LPXLARRAY createTempFpArray(int rows, int cols, double*& arrayData)
    {
        LPXLARRAY result = 0;

        result = (LPXLARRAY)TempMemory::GetMemory<BYTE>(sizeof(FP12) + (rows * cols - 1) * sizeof(double));
        result->rows = rows;
        result->columns = cols;
        arrayData = result->array;

        return result;
    }
}

#endif

