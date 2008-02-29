
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007 Eric Ehlers

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
\file XlfRef.cpp
\brief Implements the XlfRef class.
*/

// $Id$

#include <xlw/XlfRef.h>
#include <xlw/XlfOper.h>
#include <iostream>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfRef.inl>
#endif

/*!
\note In debug build, generates a message if the request is in the range.
*/
//XlfOper XlfRef::operator()(INT32 r, INT32 c) const
//{
//#if !defined(NDEBUG)
//    if (rowbegin_ + r > rowend_ || colbegin_ + c > colend_)
//  {
//    std::cerr << "XlfRef access out of range" << std::endl;
//  }
//#endif
//    XlfOper res;
//    res.Set(XlfRef(rowbegin_ + r, colbegin_ + c, sheetId_));
//    return res;
//}
