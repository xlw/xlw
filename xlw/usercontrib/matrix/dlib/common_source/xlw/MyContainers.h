//
//
//                                                            MyContainers.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne
 Copyright (C) 2009 2011 Narinder S Claire
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
/*
    everyone has their favoured matrix and array class
    You should alter this file to typedef your favourite of each to MyMatrix and MyVector.

    For MyMatrix it is assumed that a constructor with MyMatrix(size_t, size_t) exists
    and that an element can be accessed via thisMatrix[i][j]
*/

#ifndef MY_CONTAINERS_H
#define MY_CONTAINERS_H

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif


#include <xlw/MJCellMatrix.h>
#include <vector>
#include "dlib/matrix.h"
#include "dlib/array.h"

namespace xlw {

    typedef std::vector<double>  MyArray;
    typedef dlib::matrix<double>  MyMatrix;
    typedef MyMatrix NEMatrix;


    typedef impl::MJCellMatrix CellMatrixImpl;

    template<typename MatrixType>
    struct MatrixTraits
    {
        static inline double getAt(const MatrixType& A, size_t i , size_t j)
        {
            return A(i,j);
        }

        static inline void setAt(MatrixType& A, size_t i , size_t j, double value)
        {
            A(i,j) = value;
        }

        static inline MatrixType create(size_t i , size_t j)
        {
           return MatrixType(i, j);
        }

        static inline size_t rows(const MatrixType& A)
        {
            return A.nr();
        }

        static inline size_t columns(const MatrixType& A)
        {
            return A.nc();
        }
    };

    template<typename ArrayType>
    struct ArrayTraits
    {
        static inline double getAt(const ArrayType& A, size_t i)
        {
            return A[i];
        }

        static inline void setAt(ArrayType& A, size_t i, double value)
        {
            A[i] = value;
        }

        static inline ArrayType create(size_t i)
        {
            return ArrayType(i);
        }

        static inline size_t size(const ArrayType& A)
        {
            return A.size();
        }
    };
}


#endif




