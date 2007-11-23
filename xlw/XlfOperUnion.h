
/*
 Copyright (C) 2007 Eric Ehlers
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfOperUnion_H
#define INC_XlfOperUnion_H

/*!
\file XlfOperUnion.h
\brief Declares XlfOper union.
*/

// $Id: XlfOper.h 381 2007-11-20 13:08:51Z ericehlers $

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

union XlfOperUnion {
    LPXLOPER lpxloper4;
    LPXLOPER12 lpxloper12;
};

#endif
