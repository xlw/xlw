// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

// $Id$

#ifndef INC_EXCEL32_API_H
#define INC_EXCEL32_API_H

/*!
\file EXCEL32_API.h
\brief Defines the EXCEL32_API macro that flags exported classes of the framework.
*/

#include <xlw/port.h>

/*! \defgroup macros Global XLW macros
    Global definitions and quite a few macros which help porting the code to
    different compilers
    @{
*/

//! version hexadecimal number
#define XLW_HEX_VERSION 0x010100a1

//! version string
#ifdef XLW_DEBUG
    #define XLW_VERSION "1.1.0a1-cvs-debug"
#else
    #define XLW_VERSION "1.1.0a1-cvs"
#endif

//! global trace level (may be superseded locally by a greater value)
#define XLW_TRACE_LEVEL 0


#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

#if defined (_DLL) && !defined(EXCEL32_NOIMPORTEXPORT)
#ifdef EXCEL32_EXPORTS
#define EXCEL32_API PORT_EXPORT_SYMBOL
#else
#define EXCEL32_API PORT_IMPORT_SYMBOL
#endif
#else
#define EXCEL32_API
#endif

/*! @}  */

#endif