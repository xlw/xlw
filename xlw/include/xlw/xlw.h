
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 John Adcock


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// $Id$

#ifndef INC_XLW_H
#define INC_XLW_H

/*!
\file xlw.h
\brief Includes all the include files of the package.
*/

// Package files
#include <xlw/XlfArgDescList.h>
#include <xlw/XlfCmdDesc.h>
#include <xlw/XlfFuncDesc.h>
#include <xlw/XlfOper.h>
#include <xlw/XlfOper4.h>
#include <xlw/XlfOper12.h>
#include <xlw/XlfRef.h>
#include <xlw/CellMatrix.h>
#include <xlw/XlFunctionRegistration.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfServices.h>
#include <xlw/macros.h>

#if defined(_MSC_VER)
// Force export of functions implemented in XlOpenClose.h and required by Excel
// so that for msvc we don't need to use a def file
#     ifndef _WIN64
#        pragma comment (linker, "/export:_xlAutoOpen")
#        pragma comment (linker, "/export:_xlAutoClose")
#        pragma comment (linker, "/export:_xlAutoRemove")
#        ifndef NDEBUG
#            pragma comment (linker, "/export:_xlwGenDoc")
#        endif
#    else
#        pragma comment (linker, "/export:xlAutoOpen")
#        pragma comment (linker, "/export:xlAutoClose")
#        pragma comment (linker, "/export:xlAutoRemove")
#        ifndef NDEBUG
#            pragma comment (linker, "/export:xlwGenDoc")
#        endif
#    endif
#endif

#endif

