// Copyright (c) 1998-2001
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

#include "pragmas.h"

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

#ifdef _MSC_VER
#pragma once
#endif

//  Microsoft VC++ 6.0 and above
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
//! Masks the C function \c strnicmp with the more explicit Unix-like name
#define strncasecmp strnicmp
//! Masks the C function \c stricmp with the more explicit Unix-like name
#define strcasecmp stricmp
//! The compiler does not support file names longer than 8.3 characters.
#define PORT_NO_LONG_FILE_NAMES
// //! Should use old standard C headers preferably.
//#define PORT_USE_OLD_C_HEADERS
// //! Should use old standard I/O C headers preferably.
//#define PORT_USE_OLD_IO_HEADERS
//! Should not use throw standard specification declaration.
#define PORT_NO_THROW_DECLARATION
//! Should not use STL min<> and max<>.
#define PORT_DEFINE_MINMAX
//! Should not use extension container <hash_set> and <hash_map>
#define PORT_NO_HASH_TABLE
//! Partial support of member templates (if defined inline).
#define PORT_PARTIAL_MEMBER_TEMPLATE
//! Should not specialize members of template class.
#define PORT_NO_TEMPLATE_SPECIALIZATION_FOR_MEMBER
//! Should not use template partial specializarion.
#define PORT_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//! Should not declare friends as template function/class.
#define PORT_NO_TEMPLATE_FRIENDS
//! Should not use a statement return void for function returning void.
#define PORT_NO_VOID_RETURN_VALUE
//! Imports symbol if exist, for shared library.
#define PORT_IMPORT_SYMBOL __declspec(dllimport)
//! Exports symbol if exist, for shared library.
#define PORT_EXPORT_SYMBOL __declspec(dllexport)
//! Should not use covariant return type on hierarchies.
#define PORT_NO_COVARIANT_RETURN
//! Template definition have to follow the declaration in order to be instanciated.
#define PORT_TEMPLATES_REQUIRE_SOURCE

// other compiler not supported
#else
#error "Your compiler is not supported by this library, edit the port.h file"
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

#ifndef PORT_TEMPLATE_SPECIALIZATION
//! Standard template specialization declaration.
#define PORT_TEMPLATE_SPECIALIZATION
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

//! Directory separator in file path.
#ifdef unix
#define PORT_FILE_SEPARATOR '/'
#else
#define PORT_FILE_SEPARATOR '\\'
#endif

//! Standard \c type_name keyword work-around.
#ifndef PORT_TYPENAME
#define PORT_TYPENAME
#endif

#ifdef PORT_USE_SGI_STL
#include <stl_config.h>
#endif

#ifdef PORT_NO_BOOLEAN
#include <stdbool.h>
#endif

#endif
