/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*!
\file XlfException.cpp
\brief Implements the XlfException class hierarchy.
*/

// $Id$

#include <xlw/XlfException.h>
#include <xlw/XlfOper.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfException.inl>
#endif

/*!
\brief Generate error function.
An error function returns an error marshalled as a XlfOper. The function XlfException###
where ### can be Null, Div0, Value, Ref, Name, Num, or NA.
*/
#define MACRO_ERROR_IMPLEMENTATION(ERR) \
XlfOper XlfException::##ERR() { \
  return XlfOper().SetError(xlerr##ERR); \
}

//! Generates Null error (no info).
MACRO_ERROR_IMPLEMENTATION(Null);
//! Generates Divion by 0 error.
MACRO_ERROR_IMPLEMENTATION(Div0);
//! Generates bad value error.
MACRO_ERROR_IMPLEMENTATION(Value);
//! Generates bad reference error.
MACRO_ERROR_IMPLEMENTATION(Ref);
//! Generates bad name error.
MACRO_ERROR_IMPLEMENTATION(Name);
//! Generates bad number error.
MACRO_ERROR_IMPLEMENTATION(Num);
//! Generates not available error.
MACRO_ERROR_IMPLEMENTATION(NA);

#undef MACRO_ERROR_IMPLEMENTATION
