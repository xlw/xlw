// Copyright (c) 1998-2002
// Jerome Lecomte
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is"
// without express or implied warranty.

#ifndef INC_port_H
#define INC_port_H

/*!
\file port.h
\brief Portability macros.

This file is part of a broader framework, some of the macros defined here
are not used in excel32 framework.
*/

// $Id $

#include <xlw/pragmas.h>

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif


// Borland C++ 5.5
#if   defined(__BORLANDC__)
    #include <xlw/config.bcc.h>
// Metrowerks CodeWarrior
#elif defined(__MWERKS__)
    #error Unsupported compiler - please contact the XLW team
// Microsoft Visual C++ 6.0 and above
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
    #include <xlw/config.msvc.h>
// Dynamically created by configure
#elif defined(HAVE_CONFIG_H)
    #error Unsupported compiler - please contact the XLW team
// other compiler not supported
#else
    #error Unsupported compiler - please contact the XLW team
#endif


//! namespace work-around for compiler who don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_BEGIN_NAMESPACE(X)
#else
#define PORT_BEGIN_NAMESPACE(X) namespace X {
#endif

//! namespace work-around for compiler who don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_END_NAMESPACE
#else
#define PORT_END_NAMESPACE }
#endif

//! namespace work-around for compiler who don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_USING_NAMESPACE(X)
#else
#define PORT_USING_NAMESPACE(X) using namespace X
#endif

//! namespace work-around for compiler who don't support it.
#ifdef PORT_NO_NAMESPACE
#define PORT_USING(X)
#else
#define PORT_USING(X) using X
#endif

//! namespace work-around for compiler who don't support it.
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
