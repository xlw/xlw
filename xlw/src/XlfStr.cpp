
/*
 Copyright (C) 2007, 2008 Eric Ehlers

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*!
\file XlfStr.cpp
\brief Implements the XlfStr class.
*/

// $Id: XlfRef.cpp 395 2007-11-30 15:36:29Z ericehlers $

#include <xlw/XlfStr.h>
#include <xlw/XlfExcel.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

std::wstring xlw::voidToWstr(XLWSTR xlwstr) {
    if (XlfExcel::Instance().excel12()) {
        return std::wstring(static_cast<wchar_t*>(xlwstr));
    } else {
        char *c = static_cast<char*>(xlwstr);
        size_t len = strlen(c)*2+2;
        wchar_t *w = new wchar_t[len];
        mbstowcs(w, c, len);
        std::wstring ret(w);
        delete[] w;
        return ret;
    }
}

