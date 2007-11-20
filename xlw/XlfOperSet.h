
/*
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfOperSet_H
#define INC_XlfOperSet_H

/*!
\file XlfOperSet.h
\brief Declares template function XlfOperSet.
*/

// $Id: XlfOperSet.h 379 2007-11-16 12:53:30Z ericehlers $

#include <xlw/XlfExcel.h>
#include <xlw/XlfOper.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Template function to set an XlfOper to a matrix value.
/*!
This function was previously implemented as a template member function
of class XlfOper, for compilers supporting template member functions.

The implementation as a template member function is not compatible with the
new design for the XlfOperImpl so this function is now implemented solely as
a standalone template function.
*/

template <class FwdIt>
XlfOper& XlfOperSet(XlfOper& oper, RW rows, COL cols, FwdIt it)
{
    if (XlfExcel::Instance().excel12()) {

        LPXLOPER12 lpxloper=oper;
        lpxloper->xltype = xltypeMulti;
        lpxloper->val.array.rows = rows;
        lpxloper->val.array.columns = cols;
        lpxloper->val.array.lparray = (LPXLOPER12)XlfExcel::Instance().GetMemory(rows * cols * sizeof(XLOPER12));
        for (size_t i = 0; i < rows * cols; ++i, ++it)
            lpxloper->val.array.lparray[i] = *(LPXLOPER12)XlfOper(*it);
        return oper;

    } else { // Excel 4

        if (rows > USHRT_MAX) {
            std::ostringstream err;
            err << "Matrix row count " << rows << " exceeds Excel4 max " << USHRT_MAX;
            throw(err.str.c_str());
        }

        if (cols > USHRT_MAX) {
            std::ostringstream err;
            err << "Matrix col count " << cols << " exceeds Excel4 max " << USHRT_MAX;
            throw(err.str.c_str());
        }

        LPXLOPER lpxloper=oper;
        lpxloper->xltype = xltypeMulti;
        lpxloper->val.array.rows = rows;
        lpxloper->val.array.columns = cols;
        lpxloper->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(rows * cols * sizeof(XLOPER));
        for (size_t i = 0; i < rows*cols; ++i, ++it)
            lpxloper->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
        return oper;

    }

}

#endif
