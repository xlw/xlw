
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


#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"

using namespace xlw;


//<xlw:libraryname=dlib

MyMatrix // Returns the Cholesky Decomposition of the matrix
//<xlw:threadsafe
dlib_cholesky(const MyMatrix& inMat // matrix to decompose
        );

double // computes the inner product of two vectors
//<xlw:threadsafe
dlib_inner(const MyArray &x // First Vector
            , const MyArray &y // Second Vector
            );

#endif
