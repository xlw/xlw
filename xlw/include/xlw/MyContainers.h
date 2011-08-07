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

// Uncomment the line below to use boost matrix
//#define USE_XLW_WITH_BOOST_UBLAS

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <xlw/NCMatrices.h>
#include <xlw/MJCellMatrix.h>
#include <vector>

#ifdef USE_XLW_WITH_BOOST_UBLAS
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#endif

namespace xlw {

#ifdef USE_XLW_WITH_BOOST_UBLAS

    #define USE_PARENTHESESES
    typedef boost::numeric::ublas::matrix<double> MyMatrix;
    typedef boost::numeric::ublas::vector<double> MyArray;
    typedef MyMatrix NEMatrix;

#else

    // uncomment the next line if your matrix class uses round brackets
    //#define USE_PARENTHESESES
    // change the typedefs to your favourite container classes
    typedef NCMatrix MyMatrix;
    typedef std::vector<double> MyArray;
    typedef MyMatrix NEMatrix;

#endif


	typedef impl::MJCellMatrix CellMatrixImpl;


    template<typename MatrixType>
    struct MatrixTraits
    {
        static inline double getAt(const MatrixType& A, size_t i , size_t j)
        {
#ifdef USE_PARENTHESESES
            return A(i,j);
#else
            return A[i][j];
#endif
        }

        static inline void setAt(MatrixType& A, size_t i , size_t j, double value)
        {
#ifdef USE_PARENTHESESES
            A(i,j) = value;
#else
            A[i][j] = value;
#endif
        }

        static inline MatrixType create(size_t i , size_t j)
        {
            return MatrixType(i,j);
        }

        static inline size_t rows(const MatrixType& A)
        {
            return A.size1();
        }

        static inline size_t columns(const MatrixType& A)
        {
            return A.size2();
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




