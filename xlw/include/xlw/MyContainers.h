//
//
//                                                            MyContainers.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne

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

    For MyMatrix it is assumed that a constructor with MyMatrix(unsigned long, unsigned long) exists
    and that an element can be accessed via thisMatrix[i][j]
*/

#ifndef MY_CONTAINERS_H
#define MY_CONTAINERS_H

// Uncomment the line below to use boost matrix
//#define USE_XLW_WITH_BOOST_UBLAS

#include <xlw/port.h>
#include "MJMatrices.h"
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
    typedef MJMatrix MyMatrix;
    typedef std::vector<double> MyArray;
    typedef MyMatrix NEMatrix;

#endif

    double Element(const MyMatrix& A, unsigned long i , unsigned long j);

    double& ChangingElement(MyMatrix& A, unsigned long i , unsigned long j);

}

#endif

