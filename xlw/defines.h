
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004, 2004 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_defines_H
#define INC_defines_H

/*!
\file defines.h
*/

// $Id$

#if defined(_MSC_VER)
#pragma once
#endif

//! Export flag.
/*!
Export macro that tells the compiler that the function is to be exported.
*/
#define EXCEL_EXPORT __declspec(dllexport)

#define XLW__HERE__ __FILE__ "(" _MAKESTRING(__LINE__) "): "
#define _MAKESTRING(a) __MAKESTRING(a)
#define __MAKESTRING(a) #a

#endif

