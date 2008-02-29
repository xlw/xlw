
/*
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


#ifndef INC_XlfStr_H
#define INC_XlfStr_H

/*!
\file XlfStr.h
\brief Declares the XlfStr class.
*/

// $Id: XlfRef.h 395 2007-11-30 15:36:29Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

//! Experimental treatment of long strings for Excel 2007.
/*!
xxx
*/

typedef void* XLWSTR;

std::wstring voidToWstr(XLWSTR xlwstr);

#endif

