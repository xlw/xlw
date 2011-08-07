
/*
 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Narunder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "Test.h"
#include "dlib/matrix/matrix_cholesky.h"
#include <numeric>

MyMatrix // Returns the Cholesky Decomposition of the matrix
dlib_cholesky(const MyMatrix& inMat) // matrix to decompose
{
    dlib::cholesky_decomposition<MyMatrix> chol(inMat);
    if(!chol.is_spd())
    {
        throw "Matrix not semi-positive definite";
    }
    return trans(chol.get_l());
}

double // computes the inner product of two vectors
dlib_inner(const MyArray &x, const MyArray &y)
{
    if(x.size() != y.size())
    {
        throw "Arrays are different sizes";
    }
    return std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
}


