// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfException_H
#define INC_XlfException_H

/*!
\file XlfException.h
\brief Declares XlfException class hierarchy.
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

class EXCEL32_API XlfOper;

//! Excel interface exceptions
/*!
It is important to distinguish exception thrown by the Excel 
framework from the exception linked to other routines because 
they will be catched differently by the wrapper.
 
These exceptions don't necessarly correspond to errors, see
for example XlfExceptionUncalculated.
*/
class EXCEL32_API XlfException: public std::exception
{
public:
  //! Message string ctor.
  XlfException(const std::string& what = "");
  //! std::exception interface
  const char* what() const throw ();
  //! Generate a Null error, hold by the returned XlfOper.
  static XlfOper Null();
  //! Generate a Divison by 0 error, hold by the returned XlfOper.
  static XlfOper Div0();
  //! Generate a Value error, hold by the returned XlfOper.
  static XlfOper Value();
  //! Generate a Reference error, hold by the returned XlfOper.
  static XlfOper Ref();
  //! Generate a Bad name error, hold by the returned XlfOper.
  static XlfOper Name();
  //! Generate a Number expected or wrong number format error, hold by the returned XlfOper.
  static XlfOper Num();
  //! Generate a Not available error, hold by the returned XlfOper.
  static XlfOper NA();
private:
    std::string what_;
};

//! Argument cell not calculated.
/*!
A cell was requested whose value has been invalidated.

When it occurs, the framework should return immediately
to excel to let it calculate the cell. Excel will then
call again the function immediately after the argument
was re-calculated.
*/
class EXCEL32_API XlfExceptionUncalculated: public XlfException
{};

//! Abort requested.
/*!
Usually thrown by the user after XlfExcel::IsEscPressed had return true.
*/
class EXCEL32_API XlfExceptionAbort: public XlfException
{};

//! Coerce to some other data type needed.
/*!
Occurs when the data can't be manipulated as such (a string for example)
and needs to be converted (coerced) to some other type (double for example).
*/
class EXCEL32_API XlfExceptionCoerce: public XlfException
{};

//! Internal memory buffer is full.
/*!
This exception is thrown by XlfExcel::GetMemory whenever the internal 
buffer is full.
*/
class EXCEL32_API XlfExceptionBufferFull: public XlfException
{};

#ifdef NDEBUG
#include <xlw/XlfException.inl>
#endif

#endif
