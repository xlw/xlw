
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock


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
\file XlfFuncDesc.cpp
\brief Implements the XlfFuncDesc class.
*/

// $Id$

#include <xlw/XlfFuncDesc.h>
#include <xlw/XlfException.h>
#include <xlw/XlfOper4.h>
#include <xlw/XlfOper.h>
#include <algorithm>

/*!
\param name
\param alias
\param comment The first 3 argument are directly passed to
XlfAbstractCmdDesc::XlfAbstractCmdDesc.
\param category Category in which the function should appear.
\param recalcPolicy Policy to recalculate the cell.
\param Threadsafe Whether this function should be registered threadsafe under Excel 12
\param returnTypeCode The excel code for the datatype of the return value
\param helpID the help id for the function in the chm help file
\param Asynchronous does this function run Asynchronously
\param MacroSheetEquivalent should calling Excel Macro function be allowed, incompatible with multi-threading
\param ClusterSafe Can function be run on a cluster in Excel 2010
*/
xlw::XlfFuncDesc::XlfFuncDesc(const std::string& name, const std::string& alias,
                         const std::string& comment, const std::string& category,
                         RecalcPolicy recalcPolicy, bool Threadsafe, const std::string &returnTypeCode,
                         const std::string &helpID,
                         bool Asynchronous, bool MacroSheetEquivalent,
                         bool ClusterSafe)
    : XlfAbstractCmdDesc(name, alias, comment),helpID_(helpID),returnTypeCode_(returnTypeCode),
    impl_(new XlfFuncDescImpl(recalcPolicy,Threadsafe,category, Asynchronous, MacroSheetEquivalent, ClusterSafe)),
    funcId_(InvalidFunctionId)
{
}

xlw::XlfFuncDesc::~XlfFuncDesc()
{
}

/*!
The new arguments overwrite any old ones that have been previously set. You
cannot push back the arguments one by one.
*/
void xlw::XlfFuncDesc::SetArguments(const XlfArgDescList& arguments)
{
    impl_->arguments_ = arguments;
}

//int xlw::XlfFuncDesc::GetIndex() const
//{
//  return index_;
//}

//void xlw::XlfFuncDesc::SetIndex(int i_)
//{
//  index_ = i_;
//}

/*!
Registers the function as a function in excel.
\sa XlfExcel, XlfCmdDesc.
*/
int xlw::XlfFuncDesc::DoRegister(const std::string& dllName, const std::string& suggestedHelpId) const
{
    if (returnTypeCode_.empty())
        returnTypeCode_= XlfExcel::Instance().xlfOperType();
    if(returnTypeCode_ == "XLW_FP")
        returnTypeCode_= XlfExcel::Instance().fpType();
    return RegisterAs(dllName, suggestedHelpId, 1);
}

int xlw::XlfFuncDesc::DoUnregister(const std::string& dllName) const
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

// function Excel4 calls always as using XLOPER12 seem problematic
int xlw::XlfFuncDesc::RegisterAs(const std::string& dllName, const std::string& suggestedHelpId, double mode_) const
{
    // alias arguments
    XlfArgDescList& arguments = impl_->arguments_;

    int nbargs = static_cast<int>(arguments.size());
    std::string args(returnTypeCode_);
    std::string argnames;

    // the synchronous part of an asynchronous function returns void
    if (XlfExcel::Instance().excel14() && impl_->Asynchronous_)
    {
        args = ">";
    }

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

    // the synchronous part of an asynchronous function have an extra 
    // bigdata xloper on the end containing the handle
    if (XlfExcel::Instance().excel14() && impl_->Asynchronous_)
    {
        args += "X";
    }
    if (impl_->recalcPolicy_ == xlw::XlfFuncDesc::Volatile)
    {
        args+="!";
    }
    if (XlfExcel::Instance().excel12() && impl_->Threadsafe_)
    {
        args+="$";
    }
    if (XlfExcel::Instance().excel14() && impl_->ClusterSafe_)
    {
        args+="&";
    }
    if (impl_->MacroSheetEquivalent_)
    {
        args+="#";
    }

    args+='\0'; // null termination for C string

    std::vector<LPXLOPER> argArray(10 + nbargs);
    LPXLOPER *px = &argArray[0];
    std::string functionName(GetName());

    // We need to have 2 functions exposed one for less than
    // version 14 and that it the normal function, we also need
    // the Synchronous part that returns void and takes an extra int
    // By convension this is the same as the normal function but with 
    // Sync on the end
    if (XlfExcel::Instance().excel14() && impl_->Asynchronous_)
    {
        functionName += "Sync";
    }

    (*px++) = XlfOper4(dllName);
    (*px++) = XlfOper4(functionName);
    (*px++) = XlfOper4(args);
    (*px++) = XlfOper4(GetAlias());
    (*px++) = XlfOper4(argnames);
    (*px++) = XlfOper4(mode_);
    (*px++) = XlfOper4(impl_->category_);
    (*px++) = XlfOper4(""); // shortcut
    // use best help context
    if(!helpID_.empty() && helpID_ != "auto")
    {
        (*px++) = XlfOper4(helpID_);
    }
    else
    {
        (*px++) = XlfOper4(suggestedHelpId); 
    }
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

void xlw::XlfFuncDesc::DoMamlDocs(std::ostream& ostr) const
{
    ostr << "<introduction>" << std::endl;
    XlfArgDescList& arguments = impl_->arguments_;
    ostr << "<para>" << GetComment() << "</para>" << std::endl;

    std::string argnames;

    XlfArgDescList::const_iterator it = arguments.begin();
    while (it != arguments.end())
    {
        argnames += (*it).GetName();
        ++it;
        if (it != arguments.end())
            argnames+=", ";
    }

    ostr << "<code>=" << GetAlias() << "(" << argnames << ")</code>" << std::endl;
    ostr << "</introduction>" << std::endl;

    ostr << "<section>" << std::endl;
    ostr << "  <title>Parameters</title>" << std::endl;
    ostr << "  <content>" << std::endl;


    for (it = arguments.begin(); it != arguments.end(); ++it)
    {
        ostr << "    <para>";
        ostr << (*it).GetName() << ": " << (*it).GetComment();
        ostr << "</para>" << std::endl;
    }
    ostr << "  </content>" << std::endl;
    ostr << "</section>" << std::endl;
}

