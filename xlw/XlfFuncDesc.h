// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfFuncDesc_H
#define INC_XlfFuncDesc_H

/*!
\file XlfFuncDesc.h
\brief Declares class XlfFuncDesc.
*/

// $Id$

#include <xlw/XlfAbstractCmdDesc.h>

#if defined(_MSC_VER)
#pragma once
#endif

class XlfArgDescList;

//! Encapsulates a function to be registered to Excel.
/*!
By registering your function, you make it available under Excel in 
any spreadsheet as well as in the function wizard.
*/
class EXCEL32_API XlfFuncDesc: public XlfAbstractCmdDesc
{
public:
  //! Ctor
  XlfFuncDesc(const std::string& name, const std::string& alias,
              const std::string& comment, const std::string& category);
  //! Dtor.
  ~XlfFuncDesc();

  //! Sets the category where your function will appear in the function wizzard.
  void SetCategory(const std::string& category);
  //! Gets the category where your function will appear in the function wizzard.
  const std::string& GetCategory() const;
  //! Sets the arguments definition.
  void SetArguments(const XlfArgDescList& arguments);
  //! Gets the arguments definition.
  const XlfArgDescList& GetArguments() const;

protected:
  //! Registers the function (template method).
  int DoRegister(const std::string& dllName) const;

private:
  //! Default ctor is declared private but not defined.
  XlfFuncDesc(const XlfFuncDesc&);
  //! Copy otor is declared private but not defined.
  XlfFuncDesc& operator=(const XlfFuncDesc&);
  //! Pointer to implementation (pimpl idiom, see \ref HS).
  struct XlfFuncDescImpl * impl_;
};

#endif