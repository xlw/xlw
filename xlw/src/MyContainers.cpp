//
//
//                        MyContainers.cpp
//
//
/*
 Copyright (C) 2005 Mark Joshi
 Copyright (C) 2009 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/MyContainers.h>


#ifdef USE_PARENTHESESES

double xlw::Element(const MyMatrix& A, size_t i , size_t j)
{
    return A(i,j);
}

double& xlw::ChangingElement(MyMatrix& A, size_t i , size_t j)
{
    return A(i,j);
}
#else

double xlw::Element(const MyMatrix& A, size_t i , size_t j)
{
    return A[i][j];
}

double& xlw::ChangingElement(MyMatrix& A, size_t i , size_t j)
{
    return A[i][j];
}
#endif
