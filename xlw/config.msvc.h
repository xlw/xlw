
/*
 Copyright (c) 2002 Ferdinando Ametrano
 Copyright (c) 1998-2002 Jerome Lecomte

 This file is part of XLW, a free-software/open-source Excel32 C++ Wrapper
 http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw@ifrance.com
 The license is also available online at
 http://xlw.sourceforge.net/html/download.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// $Id$

#ifndef xlw_config_msvc_h
#define xlw_config_msvc_h

#pragma once

/*** libraries to be linked***/

#ifdef _DEBUG
    #pragma comment(lib,"excel32_d.lib")
#else
    #pragma comment(lib,"excel32.lib")
#endif

#ifdef _MT
    #ifndef _DLL
        #ifdef _DEBUG
            #error Set 'Debug Multithreaded DLL' under C/C++ | Code Generation 
        #else
            #error Set 'Multithreaded DLL' under C/C++ | Code Generation
        #endif
    #endif
#else
    #ifdef _DEBUG
        #error Set 'Debug Multithreaded DLL' under C/C++ | Code Generation 
    #else
        #error Set 'Multithreaded DLL' under C/C++ | Code Generation
    #endif
#endif

/*
#ifndef _CPPRTTI
    #error Check the 'C/C++ | C++ Language | Use RTTI' option
#endif

*/


//! Partial support of member templates (if defined inline).
#define PORT_PARTIAL_MEMBER_TEMPLATE
//! Imports symbol if exist, for shared library.
#define PORT_IMPORT_SYMBOL __declspec(dllimport)
//! Exports symbol if exist, for shared library.
#define PORT_EXPORT_SYMBOL __declspec(dllexport)


#endif
