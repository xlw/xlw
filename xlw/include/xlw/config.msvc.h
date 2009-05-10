
/*
 Copyright (C) 2002, 2003, 2004 Ferdinando Ametrano
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2006 Mark Joshi
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

// $Id: config.msvc.h 493 2008-03-14 15:40:30Z ericehlers $

#ifndef xlw_config_msvc_h
#define xlw_config_msvc_h

#pragma once


//
// select toolset:
//
#if (_MSC_VER < 1300)
#  error "unsupported Microsoft compiler"
#elif (_MSC_VER == 1300)
// move inside here configs specific to VC++ .Net
#  define XLW_LIB_TOOLSET "vc7"
#elif (_MSC_VER == 1310)
// move inside here configs specific to VC++ .Net 2003
#  define XLW_LIB_TOOLSET "vc71"
#  pragma warning (disable : 4800)  // forcing value to bool 'true' or 'false'
#  pragma warning (disable : 4267)  // conversion from 'size_t' to 'type', possible loss of data
#  pragma warning (disable : 4244)  // conversion from 'type1' to 'type2', possible loss of data
#  pragma warning (disable : 4311)  // pointer truncation from 'type' to 'type'
#elif (_MSC_VER == 1400)
// move inside here configs specific to VC++ .Net 2005
#  define XLW_LIB_TOOLSET "vc80"
#  pragma warning (disable : 4800)  // forcing value to bool 'true' or 'false'
#  pragma warning (disable : 4996)  // deprecated function
#elif (_MSC_VER == 1500)
// move inside here configs specific to VC++ .Net 2008
#  define XLW_LIB_TOOLSET "vc90"
#  pragma warning (disable : 4800)  // forcing value to bool 'true' or 'false'
#  pragma warning (disable : 4996)  // deprecated function
#else
#  define XLW_LIB_TOOLSET "vcxx"
#endif



/*** libraries to be linked***/


//
// select thread opt:
//
#ifdef _MT
#  define XLW_LIB_THREAD_OPT "-mt"
#else
#  define XLW_LIB_THREAD_OPT
#endif

//
// select linkage opt:
//
#ifdef _DLL
#  if defined(_DEBUG)
#    define XLW_LIB_RT_OPT "-gd"
#  else
#    define XLW_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
#    define XLW_LIB_RT_OPT "-sgd"
#  else
#    define XLW_LIB_RT_OPT "-s"
#  endif
#endif

#define XLW_LIB_NAME "xlw-" XLW_LIB_TOOLSET XLW_LIB_THREAD_OPT XLW_LIB_RT_OPT "-" XLW_LIB_VERSION ".lib"

#ifdef XLW_AUTOLINK
#   pragma comment(lib, XLW_LIB_NAME)
//#   pragma message(XLW_LIB_NAME)
#endif // XLW_AUTOLINK

//! Partial support of member templates (if defined inline).
//#define PORT_PARTIAL_MEMBER_TEMPLATE
//! Imports symbol if exist, for shared library.
#define PORT_IMPORT_SYMBOL __declspec(dllimport)
//! Exports symbol if exist, for shared library.
#define PORT_EXPORT_SYMBOL __declspec(dllexport)


#endif

