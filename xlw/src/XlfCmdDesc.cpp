
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 2011 Narinder S Claire


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
#include <xlw/XlfOper4.h>
#include <xlw/XlfException.h>
#include <iostream>
#include <xlw/macros.h>
#include <xlw/xlwshared_ptr.h>
#include <algorithm>

/*! \e see XlfAbstractCmdDesc::XlfAbstractCmdDesc(const std::string&, const std::string&, const std::string&)
*/
xlw::XlfCmdDesc::XlfCmdDesc(const std::string& name,
                            const std::string& alias,
                            const std::string& comment,
                            const std::string& menu,
                            const std::string& menuText,
                            bool hidden) :
       XlfAbstractCmdDesc(name, alias, comment), 
       menu_(menu),
       text_(menuText),
       hidden_(hidden),
       funcId_(InvalidFunctionId)
{}

xlw::XlfCmdDesc::~XlfCmdDesc()
{}

bool xlw::XlfCmdDesc::IsAddedToMenuBar()
{
  return !menu_.empty();
}

/// This function is using a naked XLOPER
int xlw::XlfCmdDesc::AddToMenuBar(const char* menu, const char* text)
{
    // allow user to override stored values
    if(menu)
    {
        menu_ = menu;
    }
    if(text)
    {
        text_ = text;
    }

    // we can only proceed if we have both
    if(menu_.empty() || text_.empty())
    {
        return 0;
    }

    //first check to see if the menu already exists
    XlfOper barNum(10);
    XlfOper menuLocation;
    XlfOper missingValue;
    XlfOper menuOper(menu_);
    int err = XlfExcel::Instance().Call(xlfGetBar, menuLocation, 3, barNum, menuOper, XlfOper(0));
    if (err || menuLocation.IsError())
    {
		// if it doesn't then we have to find the id of the last menu item on the worksheet bar
		// usually this is Help but we need to cope with internation versions so we find it by
		// searching over the bars until we get an error.
		// we skip the search at 1 as we want to fail safe and always exit with something that will work
		int menuPosition(1);
		XlfOper menuName;
		err = XlfExcel::Instance().Call(xlfGetBar, menuName, 3, barNum, XlfOper(menuPosition + 1), XlfOper(0));
		while(!err && !menuName.IsError())
		{
			++menuPosition;
			err = XlfExcel::Instance().Call(xlfGetBar, menuName, 3, barNum, XlfOper(menuPosition + 1), XlfOper(0));
		}

		// now add the menu and the first command in a single request
        XlfOper menuDesc(2,5);
        menuDesc(0,0) = menu_;
        menuDesc(0,1) = "";
        menuDesc(0,2) = "";
        menuDesc(0,3) = "";
        menuDesc(0,4) = "";
        menuDesc(1,0) = text_;
        menuDesc(1,1) = GetAlias();
        menuDesc(1,2) = "";
        menuDesc(1,3) = GetComment();
        menuDesc(1,4) = "";
        err = XlfExcel::Instance().Call(xlfAddMenu, 0, 3, barNum, menuDesc, XlfOper(menuPosition));
        if(err != xlretSuccess)
		{
			// continue on failure but would be good to get reports if this happens
            std::cerr << XLW__HERE__ << "Add Menu " <<  menu_.c_str() << " failed" << std::endl;
		}
    }
	else
	{
		// if the bar is already there then add the current commamnd
		XlfOper command(1,4);
		command(0,0) = text_;
		command(0,1) = GetAlias();
		command(0,2) = "";
		command(0,3) = GetComment();

		err = XlfExcel::Instance().Call(xlfAddCommand, 0, 3, barNum, menuOper, command);
		if (err != xlretSuccess)
		{
			// continue on failure but would be good to get reports if this happens
			std::cerr << XLW__HERE__ << "Add command " << GetName().c_str() << " to " << menu_.c_str() << " failed" << std::endl;
		}
	}
    return err;
}

int xlw::XlfCmdDesc::Check(bool ERR_CHECK) const
{
    if (menu_.empty())
    {
        std::cerr << XLW__HERE__ << "No menu specified for the command \"" << GetName().c_str() << "\"" << std::endl;
        return xlretFailed;
    }
    int err = XlfExcel::Instance().Call(xlfCheckCommand, 0, 4, XlfOper(10), XlfOper(menu_), XlfOper(text_), XlfOper(ERR_CHECK));
    if (err != xlretSuccess)
    {
        std::cerr << XLW__HERE__ << "Registration of " << GetAlias().c_str() << " failed" << std::endl;
        return err;
    }
    return xlretSuccess;
}

void xlw::XlfCmdDesc::RemoveFromMenuBar()
{
    // first check that the menu exists and then delete this command
    XlfOper barNum(10);
    XlfOper menu(menu_);
    XlfOper menuLocation;
    int err = XlfExcel::Instance().Call(xlfGetBar, menuLocation, 3, barNum, menu, XlfOper(0));
    if (!err && !menuLocation.IsError())
    {
        err = XlfExcel::Instance().Call(xlfDeleteCommand, 0, 3, barNum, menu, XlfOper(text_));
        if(err != xlretSuccess) 
            std::cerr << XLW__HERE__ << "Delete Command " << GetName().c_str() << " from " << menu_.c_str() <<  " failed" << std::endl;

        // check if the menu is now empty, if it is then delete it
        // if it is empty then the first item won't exist
        XlfOper firstItemLocation;
        err = XlfExcel::Instance().Call(xlfGetBar, firstItemLocation, 3, XlfOper(10), menu, XlfOper(1));
        if(!err && firstItemLocation.IsError())
        {
            err = XlfExcel::Instance().Call(xlfDeleteMenu, 0, 2, barNum, menu);
            if(err != xlretSuccess)
                std::cerr << XLW__HERE__ << "Delete Menu " << menu_.c_str() <<  " failed" << std::endl;
        }
    }
}


/*!
Registers the command as a macro in excel.
\sa XlfExcel, XlfFuncDesc.
*/
int xlw::XlfCmdDesc::DoRegister(const std::string& dllName, const std::string& suggestedHelpId) const
{
    XlfArgDescList arguments = GetArguments();

    // 2 = normal macro, 0 = hidden command
    double type = hidden_ ? 0 : 2;

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

    // When the arguments add up to more then 255 char is problematic. the functions
    // will not register see  see BUG ID: 2834715 on sourceforge - nc
    if(argnames.length() > 255)
    {
        argnames = "Too many arguments for Function Wizard";
    }

    std::vector<LPXLOPER> argArray(10 + nbargs);
    LPXLOPER *px = &argArray[0];

    (*px++) = XlfOper4(dllName);
    (*px++) = XlfOper4(GetName());
    (*px++) = XlfOper4(args);
    (*px++) = XlfOper4(GetAlias());
    (*px++) = XlfOper4(argnames);
    (*px++) = XlfOper4(type);
    (*px++) = XlfOper4("");
    (*px++) = XlfOper4("");
    (*px++) = XlfOper4("");
    (*px++) = XlfOper4(GetComment());
    int counter(0);
    for (it = arguments.begin(); it != arguments.end(); ++it)
    {
        ++counter;
        if(counter < nbargs)
        {
            (*px++) = XlfOper4((*it).GetComment());
        }
        else
        {
            // add dot space to last comment to work around known excel bug
            // see http://msdn.microsoft.com/en-us/library/bb687841.aspx
            (*px++) = XlfOper4((*it).GetComment() + ". ");
        }
    }

    if(XlfExcel::Instance().excel12())
    {
        // total number of arguments limited to 255
        // so we can't send more than 245 argument comments
        nbargs = std::min(nbargs, 245);
    }
    else
    {
        // you can't send more than 30 arguments to the register function
        // in up to version 2003, so just only send help for up to the first 20 parameters
        nbargs = std::min(nbargs, 20);
    }

    XlfOper4 res;
    int err = XlfExcel::Instance().Call4v(xlfRegister, res, 10 + nbargs, &argArray[0]);
    if(err == xlretSuccess && res.IsNumber())
    {
        funcId_ = res.AsDouble();
    }
    else
    {
        funcId_ = InvalidFunctionId;
    }
    return err;
}

int xlw::XlfCmdDesc::DoUnregister(const std::string& dllName) const
{
    if(funcId_ != InvalidFunctionId)
    {
        // slightly pointless as it doesn't work but we're supposed to deregister
        // the name as well as the function
        XlfExcel::Instance().Call(xlfSetName, NULL, 1, XlfOper(GetAlias()));

        XlfOper unreg;
        int err = XlfExcel::Instance().Call(xlfUnregister, unreg, 1, XlfOper(funcId_));
        return err;
    }
    else
    {
        return xlretSuccess;
    }
}

void xlw::XlfCmdDesc::DoMamlDocs(std::ostream& ostr) const
{
    ostr << "<introduction>" << std::endl;
    ostr << "<para>" << GetComment() << "</para>" << std::endl;
    ostr << "</introduction>" << std::endl;
}
