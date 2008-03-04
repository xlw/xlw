
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfCmdDesc_H
#define INC_XlfCmdDesc_H

/*!
\file XlfCmdDesc.h
\brief Class XlfCmdDesc - Encapsulates Excel C macro command
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
Commands can be called from the tool bar and do not take any arguments
*/
class EXCEL32_API XlfCmdDesc: public XlfAbstractCmdDesc
{
public:
    //! \name Structors and static members
    //@{
    //! Ctor.
    XlfCmdDesc(const std::string& name, const std::string& alias, const std::string& comment, const bool hidden);
    //! Dtor.
    ~XlfCmdDesc();
    //@}

    //! \name Management of command properties
    //@{
    //! Adds the command to an Excel menu bar.
    int AddToMenuBar(const std::string& menu, const std::string& text);
    //! Is the command already in a menu bar?
    bool IsAddedToMenuBar();
    //! Activates/Deactivates the check box next to the command menu.
    int Check(bool) const;
    //@}
protected:
    //! \name Registration
    //@{
    //! Registers the command to Excel
    int DoRegister(const std::string& dllName) const;
    //! Unregisters the function (template method).
    int DoUnregister(const std::string& dllName) const;
    //@}
private:
  //! Menu in which the command is to be displayed.
  std::string menu_;
  //! Text in the menu.
  std::string text_;
  //! Hidden flag
  bool hidden_;
};

#endif

