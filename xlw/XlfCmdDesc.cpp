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
\file XlfCmdDesc.cpp
\brief Implements the XlfCmdDesc class.
*/

// $Id$

#include <xlw/XlfCmdDesc.h>
#include <xlw/XlfOper.h>
#include <xlw/ERR_Macros.h>
#include <xlw/XlfException.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

/*! \e see XlfAbstractCmdDesc::XlfAbstractCmdDesc(const std::string&, const std::string&, const std::string&)
*/
XlfCmdDesc::XlfCmdDesc(const std::string& name, const std::string& alias, const std::string& comment)
    :XlfAbstractCmdDesc(name, alias, comment), menu_()
{}

XlfCmdDesc::~XlfCmdDesc()
{}

bool XlfCmdDesc::IsAddedToMenuBar()
{
  return !menu_.empty();
}

int XlfCmdDesc::AddToMenuBar(const std::string& menu, const std::string& text)
{
	XLOPER xMenu;
	LPXLOPER pxMenu;
	LPXLOPER px;

	menu_ = menu;
	text_ = text;

	// This is a small trick to allocate an array 5 XlfOper
	// One must first allocate the array with XLOPER
//	px = pxMenu = (LPXLOPER)new XLOPER[5];
	px = pxMenu = new XLOPER[5];
	// and then assign the XLOPER to XlfOper specifying false
	// to tell the Framework that the data is not owned by
	// Excel and that it should not call xlFree when destroyed
	XlfOper(px++, false).Set(text_.c_str());
	XlfOper(px++, false).Set(GetAlias().c_str());
	XlfOper(px++, false).Set("");
	XlfOper(px++, false).Set(GetComment().c_str());
	XlfOper(px++, false).Set("");

	xMenu.xltype = xltypeMulti;
	xMenu.val.array.lparray = pxMenu;
	xMenu.val.array.rows = 1;
	xMenu.val.array.columns = 5;

	int err = XlfExcel::Instance().Call(xlfAddCommand, 0, 3, (LPXLOPER)XlfOper(1.0), (LPXLOPER)XlfOper(menu_.c_str()), (LPXLOPER)&xMenu);
	ERR_CHECKW(err == xlretSuccess,"Add command " << GetName().c_str() << " to " << menu_.c_str() << " failed");
	delete[] pxMenu;
	return err;
}

int XlfCmdDesc::Check(bool ERR_CHECK) const
{
	ERR_CHECKX2(!menu_.empty(), XlfException,"The command '" << GetName().c_str() << "' was not added to any menu");
	int err = XlfExcel::Instance().Call(xlfCheckCommand, 0, 4, (LPXLOPER)XlfOper(1.0), (LPXLOPER)XlfOper(menu_.c_str()), (LPXLOPER)XlfOper(text_.c_str()), (LPXLOPER)XlfOper(ERR_CHECK));
	if (err != xlretSuccess)
	{
		ERR_LOGW("ERR_CHECK of " << GetAlias().c_str() << " failed");
		return err;
	}
	return xlretSuccess;
}

/*!
Registers the command as a macro in excel.
\sa XlfExcel, XlfFuncDesc.
*/
int XlfCmdDesc::DoRegister() const
{
	const std::string& dllname = XlfExcel::Instance().GetName();
	ERR_CHECKX2(!dllname.empty(), XlfException,"Library name is not initialized");
//	ERR_LOG("Registering command \"" << alias_.c_str() << "\" from \"" << name_.c_str() << "\" in \"" << dllname.c_str() << "\"");
	int err = XlfExcel::Instance().Call(
		xlfRegister, NULL, 7,
		(LPXLOPER)XlfOper(dllname.c_str()),
		(LPXLOPER)XlfOper(GetName().c_str()),
		(LPXLOPER)XlfOper("A"),
		(LPXLOPER)XlfOper(GetAlias().c_str()),
		(LPXLOPER)XlfOper(""),
		(LPXLOPER)XlfOper(2.0),
		(LPXLOPER)XlfOper(""));
	return err;
}

