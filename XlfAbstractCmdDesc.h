// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfAbstractCmdDesc_H
#define INC_XlfAbstractCmdDesc_H

/*!
\file XlfAbstractCmdDesc.h
\brief Declares class XlfAbstractCmdDesc.
*/

#include "EXCEL32_API.h"
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Abstract command.
class EXCEL32_API XlfAbstractCmdDesc
{
public:
  //! Ctor.
  XlfAbstractCmdDesc(const std::string& name, const std::string& alias, const std::string& comment);
  //! Dtor.
  virtual ~XlfAbstractCmdDesc();
  //! Registers the command to Excel.
  void Register() const;
  //! Unregister the command from Excel.
  void Unregister();

  //! Sets the name of the command in the XLL
  void SetName(const std::string& name);
  //! Gets the name of the command in the XLL.
  const std::string& GetName() const;
  //! Sets the alias to be shown in Excel
  void SetAlias(const std::string& alias);
  //! Gets the alias to be shown in Excel.
  const std::string& GetAlias() const;
  //! Sets the comment string to be shown in the function wizzard.
  void SetComment(const std::string& comment);
  //! Gets the comment string to be shown in the function wizzard.
  const std::string& GetComment() const;

protected:
  //! Actually registers the command (see template method in \ref DP)
  virtual int DoRegister(const std::string& dllName) const = 0;

private:
  //! Name of the command in the XLL.
  std::string name_;
  //! Alias for the command in Excel.
  std::string alias_;
  //! Comment associated to the command.
  std::string comment_;
};

#endif