// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_pragmas_H
#define INC_pragmas_H

/*!
\file pragmas.h
\brief Pragmas directives are to be included before any header. 

There is not much about this file, it mainly deactives the warning C4251,
C4275 and C4786. The later also guards against a bug in MSVC 6.0 that
causes C4786 to reappear even though you already deactivated it. see
http://www.deja.com for more information about C4786.
*/

// $Id$

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

#if defined(_MSC_VER)
#pragma once

//! Work around used by PORT_QUOTE
#define PORT_QUOTE(x) #x
//! Encloses the argument between quotes
#define PORT_QUOTE_VALUE(x) PORT_QUOTE(x)
//! Displays the message passed in argument (use quotes) with file and line number. 
#define PORT_MESSAGE(msg) message(__FILE__"("PORT_QUOTE_VALUE(__LINE__)") : " msg)

// C4251: <identifier> : class <XXX> needs to have dll-interface
// to be used by clients of class <YYY>
#pragma warning( disable : 4251 )

// C4275: non dll-interface class <XXX> used as base for
// dll-interface class <YYY>
#pragma warning( disable : 4275 )

// C4786:'identifier' : identifier was truncated to 'number' characters 
// in the debug information
// You should include the pragmas.h *before* any STL header. This trick
// warns you if you fail to include it first.
#if defined(_YVALS)
#pragma message(__FILE__ "(37) : USER WNG : pragma.h included too late to deactive warning 4786.")
#endif
#pragma warning( disable : 4786 )
#include <yvals.h>
#pragma warning( default : 4786 )
#pragma warning( disable : 4786 )

#endif

#endif