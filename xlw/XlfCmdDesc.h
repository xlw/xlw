// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfCmdDesc_H
#define INC_XlfCmdDesc_H

/*!
\file XlfCmdDesc.h
\brief Declares class XlfCmdDesc.
*/

// $Id$

#include <xlw/XlfAbstractCmdDesc.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Encapsulates Excel C macro command.
/*!
Commands can be called from the tool bar and do not take any argument
*/
class EXCEL32_API XlfCmdDesc: public XlfAbstractCmdDesc
{
public:
  //! Ctor.
  XlfCmdDesc(const std::string& name, const std::string& alias, const std::string& comment);
  //! Dtor.
  ~XlfCmdDesc();
  //! Adds the command to an Excel menu bar.
  int AddToMenuBar(const std::string& menu, const std::string& text);
  //! Is the command already in a menu bar?
  bool IsAddedToMenuBar();
  //! Activates/Desactivates the check box next to the command menu.
  int Check(bool) const;

protected:
  //! Registers the command to Excel
  int DoRegister() const;

private:
  //! Menu in which the command is to be displayed.
  std::string menu_;
  //! Text in the menu.
  std::string text_;
};

#endif