// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfArgDesc_H
#define INC_XlfArgDesc_H

/*!
\file XlfArgDesc.h
\brief Declares class XlfArgDesc.
*/

#include "EXCEL32_API.h"
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Encapsulates the argument definition.
/*!
Stores the name, the type (defaults to R), and a comment line to be displayed in
the function wizard.
*/
class EXCEL32_API XlfArgDesc
{
public:
  //! Default ctor.
  XlfArgDesc();
  //! Detailed ctor.
  XlfArgDesc(const std::string& name, const std::string& comment, char type='R');
  //! Dtor
  ~XlfArgDesc();
  //! Set the name of the argument
  void SetName(const std::string& name);
  //! Get the name
  const std::string& GetName() const;
  //! Set the help string associated
  void SetComment(const std::string& comment);
  //! Get the comment string
  const std::string& GetComment() const;
  //! Get the argument type
  char GetType() const;

private:
  //! Name of the argument as it appears in Excel,
  std::string name_;
  //! Comment line associated to the comment (appears in function wizzard).
  std::string comment_;
  //! Type of the argument (see Excel documentation).
  char type_;
  //! Controls the name is valid to be used properly by the function wizzard.
  void CheckNameLength();
};

#endif