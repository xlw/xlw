/*
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


#ifndef INC_XlfWindows_H
#define INC_XlfWindows_H

// put on seat belts
#ifndef STRICT
#define STRICT
#endif

// avoid use of min max macros
// that conflict with std::min/max
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef _MSC_VER
// need to undefine for mingw
#undef  UNICODE
#undef _UNICODE
#endif

// only include the important stuff
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _MSC_VER
// shouldn't really be required
// but the mingw headers set OpenThread as 0x0500
// minimum
#ifndef WINVER
#define WINVER 0x0500
#endif
#else
// with msvc allow standard 2000 minimum
#define WINVER 0x0400
#endif

#include <windows.h>

#endif
