
/*
 Copyright (c) 2002, 2003, 2004 Ferdinando Ametrano
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 J�r�me Lecomte

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

#ifndef xlw_config_msvc_h
#define xlw_config_msvc_h

#pragma once

/*** libraries to be linked***/

#ifdef XLW_AUTOLINK
#ifndef NDEBUG
#pragma comment(lib,"xlwd.lib")
#else
#pragma comment(lib,"xlw.lib")
#endif
#endif // XLW_AUTOLINK

//! Partial support of member templates (if defined inline).
#define PORT_PARTIAL_MEMBER_TEMPLATE
//! Imports symbol if exist, for shared library.
#define PORT_IMPORT_SYMBOL __declspec(dllimport)
//! Exports symbol if exist, for shared library.
#define PORT_EXPORT_SYMBOL __declspec(dllexport)


#endif
