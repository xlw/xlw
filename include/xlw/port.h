
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_port_H
#define INC_port_H

/*!
\file port.h
\brief Portability macros.

This file is part of a broader framework, some of the macros defined here
are not used in excel32 framework.
*/

// $Id$

#include <xlw/pragmas.h>

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif


#if defined(_MSC_VER)               // Microsoft Visual C++
    #include <xlw/config.msvc.h>
#elif defined(__MINGW32__)          // Minimalistic GNU for Windows
    #include <xlw/config.mgw.h>
//#if   defined(__BORLANDC__)         // Borland C++
//    #include <xlw/config.bcc.h>
#else                               // other compiler not supported
    #error Unsupported compiler - please contact the XLW team
#endif


//! namespace work-around for compilers which don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_BEGIN_NAMESPACE(X)
#else
#define PORT_BEGIN_NAMESPACE(X) namespace X {
#endif

//! namespace work-around for compilers which don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_END_NAMESPACE
#else
#define PORT_END_NAMESPACE }
#endif

//! namespace work-around for compilers which don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_USING_NAMESPACE(X)
#else
#define PORT_USING_NAMESPACE(X) using namespace X
#endif

//! namespace work-around for compilers which don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_USING(X)
#else
#define PORT_USING(X) using X
#endif

//! namespace work-around for compilers which don't support it.
#if defined(PORT_NO_NAMESPACE) && !defined(std)
#define std
#endif

#ifndef PORT_GCC_TEMPLATE_FRIEND
//! Template friend declaration
#define PORT_GCC_TEMPLATE_FRIEND
#endif

//! Exception specification declaration : no exception thrown from this function.
#ifdef PORT_NO_THROW_DECLARATION
#define DECLARE_THROW_0
#else
#define DECLARE_THROW_0 throw()
#endif

//! Exception specification declaration : exception of type \e ex thrown from this function.
#ifdef PORT_NO_THROW_DECLARATION
#define DECLARE_THROW_1(ex)
#else
#define DECLARE_THROW_1(ex) throw(ex)
#endif

#ifdef PORT_USE_SGI_STL
#include <stl_config.h>
#endif

#ifdef PORT_NO_BOOLEAN
#include <stdbool.h>
#endif

#endif

