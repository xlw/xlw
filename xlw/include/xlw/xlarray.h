/*
 Copyright (C) 2006 Mark Joshi


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
#include "MyContainers.h"

namespace xlw {

    struct xlarray
    {
        WORD rows;
        WORD columns;
        double data[1];
    };


    typedef xlarray* LPXLARRAY;


    NEMatrix GetMatrix(LPXLARRAY);

}

#endif

