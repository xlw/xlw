// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

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
