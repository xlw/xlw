/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2011 John Adcock


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

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

    //! union of the 2 FP types
    struct xlarray
    {
        union
        {
            FP fp;
            FP12 fp12;
        };
    };


    //! Interpreted as FP (Excel 4) or FP12 (Excel 12).
    typedef xlarray* LPXLARRAY;

    //! convert an incoming excel array into our matrix type
    inline NEMatrix GetMatrix(LPXLARRAY input)
    {
        size_t rows;
        size_t cols;
        double* values;
        if(XlfExcel::Instance().excel12())
        {
            rows = input->fp12.rows;
            cols = input->fp12.columns;
            values = input->fp12.array;
        }
        else
        {
            rows = input->fp.rows;
            cols = input->fp.columns;
            values = input->fp.array;
        }

        NEMatrix result(MatrixTraits<NEMatrix>::create(rows,cols));
        for (size_t i=0; i < rows; ++i)
        {
            for (size_t j=0; j < cols; ++j)
            {
                size_t k = i*cols+j;
                double val = values[k];
                MatrixTraits<NEMatrix>::setAt(result, i, j, val);
            }
        }
        return result;
    }

    inline void extractArrayInfo(const LPXLARRAY input, int& rows, int& cols, double*& arrayData)
    {
        if(XlfExcel::Instance().excel12())
        {
            rows = input->fp12.rows;
            cols = input->fp12.columns;
            arrayData = input->fp12.array;
        }
        else
        {
            rows = input->fp.rows;
            cols = input->fp.columns;
            arrayData = input->fp.array;
        }
    }

    inline LPXLARRAY createTempFpArray(int rows, int cols, double*& arrayData)
    {
        LPXLARRAY result = 0;
        if(XlfExcel::Instance().excel12())
        {
            result = (LPXLARRAY)TempMemory::GetMemory<BYTE>(sizeof(FP12) + (rows * cols - 1) * sizeof(double));
            result->fp12.rows = rows;
            result->fp12.columns = cols;
            arrayData = result->fp12.array;
        }
        else
        {
            result = (LPXLARRAY)TempMemory::GetMemory<BYTE>(sizeof(FP) + (rows * cols - 1) * sizeof(double));
            result->fp.rows = rows;
            result->fp.columns = cols;
            arrayData = result->fp.array;
        }
        return result;
    }
}

#endif

