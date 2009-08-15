
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 Narinder S Claire


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
\file XlfCmdDesc.cpp
\brief Implements the XlfCmdDesc class.
*/

// $Id: XlfCmdDesc.cpp 474 2008-03-05 15:40:40Z ericehlers $

#include <xlw/XlfCmdDesc.h>
#include <xlw/XlfOper4.h>
#include <xlw/XlfException.h>
#include <iostream>
#include <xlw/macros.h>
// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

/*! \e see XlfAbstractCmdDesc::XlfAbstractCmdDesc(const std::string&, const std::string&, const std::string&)
*/
xlw::XlfCmdDesc::XlfCmdDesc(const std::string& name, const std::string& alias, const std::string& comment, const bool hidden)
    :XlfAbstractCmdDesc(name, alias, comment), menu_(), hidden_(hidden)
{}

xlw::XlfCmdDesc::~XlfCmdDesc()
{}

bool xlw::XlfCmdDesc::IsAddedToMenuBar()
{
  return !menu_.empty();
}

/// This function is using a naked XLOPER
/// It needs updating for Excel 2007 - nc
int xlw::XlfCmdDesc::AddToMenuBar(const std::string& menu, const std::string& text)
{
    XLOPER xMenu;
    LPXLOPER pxMenu;
    LPXLOPER px;

    menu_ = menu;
    text_ = text;

    // This is a small trick to allocate an array of XlfOpers
    // One must first allocate the array with XLOPERs...
    //px = pxMenu = (LPXLOPER)new XLOPER[5];
    px = pxMenu = new XLOPER[5];
    // ...and then assign the XLOPERs to XlfOpers, specifying false to tell the
    // Framework that the data is not owned by Excel and not to call xlFree
    // during destruction
    XlfOper(px++).Set(text_.c_str());
    XlfOper(px++).Set(GetAlias().c_str());
    XlfOper(px++).Set("");
    XlfOper(px++).Set(GetComment().c_str());
    XlfOper(px++).Set("");

    xMenu.xltype = xltypeMulti;
    xMenu.val.array.lparray = pxMenu;
    xMenu.val.array.rows = 1;
    xMenu.val.array.columns = 5;

    //int err = XlfExcel::Instance().Call(xlfAddCommand, 0, 3, (LPXLOPER)XlfOper(1.0), (LPXLOPER)XlfOper(menu_.c_str()), (LPXLOPER)&xMenu);
    int err = XlfExcel::Instance().Call4(xlfAddCommand, 0, 3, (LPXLFOPER)XlfOper(1.0), (LPXLFOPER)XlfOper(menu_), (LPXLFOPER)&xMenu);
    if (err != xlretSuccess)
    std::cerr << XLW__HERE__ << "Add command " << GetName().c_str() << " to " << menu_.c_str() << " failed" << std::endl;
    delete[] pxMenu;
    return err;
}

int xlw::XlfCmdDesc::Check(bool ERR_CHECK) const
{
    if (menu_.empty())
    {
        std::cerr << XLW__HERE__ << "No menu specified for the command \"" << GetName().c_str() << "\"" << std::endl;
        return xlretFailed;
    }
    //int err = XlfExcel::Instance().Call(xlfCheckCommand, 0, 4, (LPXLOPER)XlfOper(1.0), (LPXLOPER)XlfOper(menu_.c_str()), (LPXLOPER)XlfOper(text_.c_str()), (LPXLOPER)XlfOper(ERR_CHECK));
    int err = XlfExcel::Instance().Call(xlfCheckCommand, 0, 4, (LPXLFOPER)XlfOper(1.0), (LPXLFOPER)XlfOper(menu_), (LPXLFOPER)XlfOper(text_), (LPXLFOPER)XlfOper(ERR_CHECK));
    if (err != xlretSuccess)
    {
        std::cerr << XLW__HERE__ << "Registration of " << GetAlias().c_str() << " failed" << std::endl;
        return err;
    }
    return xlretSuccess;
}

/*!
Registers the command as a macro in excel.
\sa XlfExcel, XlfFuncDesc.
*/
int xlw::XlfCmdDesc::DoRegister(const std::string& dllName) const
{

    XlfArgDescList arguments = GetArguments();

    // 2 = normal macro, 0 = hidden command
    double type = hidden_ ? 0 : 2;

    /*
    //ERR_LOG("Registering command \"" << alias_.c_str() << "\" from \"" << name_.c_str() << "\" in \"" << dllname.c_str() << "\"");
    int err = XlfExcel::Instance().Call(
        xlfRegister, NULL, 7,
        (LPXLOPER)XlfOper(dllName.c_str()),
        (LPXLOPER)XlfOper(GetName().c_str()),
        (LPXLOPER)XlfOper("A"),
        (LPXLOPER)XlfOper(GetAlias().c_str()),
        (LPXLOPER)XlfOper(""),
        (LPXLOPER)XlfOper(type),
        (LPXLOPER)XlfOper(""));
    int err = XlfExcel::Instance().Call(
        xlfRegister, NULL, 7,
        (LPXLFOPER)XlfOper(dllName.c_str()),
        (LPXLFOPER)XlfOper(GetName().c_str()),
        (LPXLFOPER)XlfOper("A"),
        (LPXLFOPER)XlfOper(GetAlias().c_str()),
        (LPXLFOPER)XlfOper(""),
        (LPXLFOPER)XlfOper(type),
        (LPXLFOPER)XlfOper(""));
    return err;
    */

    int nbargs = static_cast<int>(arguments.size());
    std::string args("A");
    std::string argnames;

    XlfArgDescList::const_iterator it = arguments.begin();
    while (it != arguments.end())
    {
        argnames += (*it).GetName();
        args += (*it).GetType();
        ++it;
        if (it != arguments.end())
            argnames+=", ";
    }

    LPXLFOPER *rgx = new LPXLFOPER[10 + nbargs];
    LPXLFOPER *px = rgx;

    (*px++) = XlfOper(dllName);
    (*px++) = XlfOper(GetName());
    (*px++) = XlfOper(args);
    (*px++) = XlfOper(GetAlias());
    (*px++) = XlfOper(argnames);
    (*px++) = XlfOper(type);
    (*px++) = XlfOper("");
    (*px++) = XlfOper("");
    (*px++) = XlfOper("");
    (*px++) = XlfOper(GetComment());
    for (it = arguments.begin(); it != arguments.end(); ++it)
    {
        (*px++) = XlfOper((*it).GetComment());
    }

    int err = static_cast<int>(XlfExcel::Instance().Callv(xlfRegister, NULL, 10 + nbargs, rgx));
    delete[] rgx;
    return err;

}

int xlw::XlfCmdDesc::DoUnregister(const std::string& dllName) const
{
    return xlretSuccess;
}

