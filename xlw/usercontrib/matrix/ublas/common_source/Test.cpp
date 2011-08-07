
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

MyMatrix // Returns the Cholesky Decomposition of the matrix
    ublas_cholesky(const MyMatrix& sym) // matrix to decompose
{
    // uBLAS doesn't contain this function so we supply a simple
    // version of the Cholesky–Crout algorithm
    if(sym.size1() == 0 || sym.size2() == 0)
    {
        return MyMatrix();
    }
    if(sym.size1() != sym.size2())
    {
        throw "Input matrix not square";
    }

    MyMatrix result(sym.size1(), sym.size1());
    size_t rows(sym.size1());
    if(sym(0, 0) <= 0.0)
    {
        throw "matrix not positive definite";
    }
    result(0, 0) = sqrt(sym(0, 0));

    for(size_t j(1); j < rows; ++j)
    {
        result(0, j) = sym(0, j) / result(0, 0);
    }

    for (size_t i(1); i < rows; ++i)
    {
        double sum(0.0);
        for(size_t j(0); j < i; ++j)
        {
            sum += result(j, i) * result(j, i);
            result(i, j) = 0.0;
        }
        if(sum >= sym(i, i))
        {
            throw "matrix not positive definite";
        }
        result(i, i) = sqrt(sym(i, i) - sum);


        for(size_t j(i+1); j < rows; ++j)
        {
            double sum(0.0);

            for (size_t sumIter(0); sumIter < i; ++sumIter)
            {
                sum += result(sumIter, i) * result(sumIter, j);
            }
            result(i, j) = (sym(i, j) - sum) / result(i, i);
        }
    }
    return result;
}

double // computes the inner product of two vectors
    ublas_inner(const MyArray &x, const MyArray &y)
{
    if(x.size() != y.size())
    {
        throw "Arrays are different sizes";
    }
    return inner_prod(x, y);
}
