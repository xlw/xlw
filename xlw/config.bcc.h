
/*
 Copyright (c) 2002 Ferdinando Ametrano

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

#ifndef xlw_config_bcc_h
#define xlw_config_bcc_h




//! Partial support of member templates (if defined inline).
#define PORT_PARTIAL_MEMBER_TEMPLATE
//! Imports symbol if exist, for shared library.
#define PORT_IMPORT_SYMBOL __declspec(dllimport)
//! Exports symbol if exist, for shared library.
#define PORT_EXPORT_SYMBOL __declspec(dllexport)


#endif
