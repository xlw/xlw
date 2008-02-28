
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007 Eric Ehlers

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
#include <xlw/XlfExcel.h>
#include <xlw/XlfException.h>
#include <xlw/XlfOper4.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

//! Internal implementation of XlfFuncDesc.
struct XlfFuncDescImpl
{
  //! Ctor.
  XlfFuncDescImpl(XlfFuncDesc::RecalcPolicy recalcPolicy, bool Threadsafe,
      const std::string& category): recalcPolicy_(recalcPolicy), Threadsafe_(Threadsafe), category_(category)
  {}
  //! Recalculation policy
  XlfFuncDesc::RecalcPolicy recalcPolicy_;
  //! Category where the function is displayed in the function wizard.
  std::string category_;
  //! List of the argument descriptions of the function.
  XlfArgDescList arguments_;
  //! Flag indicating whether this function is threadsafe in Excel 2007.
  bool Threadsafe_;
};

/*!
\param name
\param alias
\param comment The first 3 argument are directly passed to
XlfAbstractCmdDesc::XlfAbstractCmdDesc.
\param category Category in which the function should appear.
\param recalcPolicy Policy to recalculate the cell.
*/
XlfFuncDesc::XlfFuncDesc(const std::string& name, const std::string& alias,
                         const std::string& comment, const std::string& category,
                         RecalcPolicy recalcPolicy, bool Threadsafe)
    :XlfAbstractCmdDesc(name, alias, comment), impl_(0)
{
  impl_ = new XlfFuncDescImpl(recalcPolicy,Threadsafe,category);
}

XlfFuncDesc::~XlfFuncDesc()
{
  delete impl_;
}

/*!
The new arguments replace all the old one (if any set). You can not
push back the arguments one by one.
*/
void XlfFuncDesc::SetArguments(const XlfArgDescList& arguments)
{
  impl_->arguments_ = arguments;
}

//int XlfFuncDesc::GetIndex() const
//{
//  return index_;
//}

//void XlfFuncDesc::SetIndex(int i_)
//{
//  index_ = i_;
//}

/*!
Registers the function as a function in excel.
\sa XlfExcel, XlfCmdDesc.
*/
int XlfFuncDesc::DoRegister(const std::string& dllName) const
{
  //live_ = true;
  return RegisterAs(dllName, 1);
}

int XlfFuncDesc::DoUnregister(const std::string& dllName) const
{
  //live_ = false;

  XlfArgDescList arguments = GetArguments();
  size_t nbargs = arguments.size();
    std::string args(XlfExcel::Instance().xlfOperType());
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

    double funcId;
  int err = RegisterAs(dllName, 0, &funcId);

  XlfOper unreg;
  //err = Excel4(xlfUnregister, unreg, 1, XlfOper(funcId));
  //err = static_cast<int>(XlfExcel::Instance().Call4(xlfUnregister, unreg, 1, XlfOper(funcId)));
  err = static_cast<int>(XlfExcel::Instance().Call4(xlfUnregister, unreg, 1, static_cast<LPXLOPER>(XlfOper(funcId))));

  return err;
}

int XlfFuncDesc::RegisterAs(const std::string& dllName, double mode_, double* funcId) const
{

    // alias arguments
    XlfArgDescList& arguments = impl_->arguments_;

    size_t nbargs = arguments.size();
    std::string args(argType());
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
    if (impl_->recalcPolicy_ == XlfFuncDesc::Volatile)
    {
        args+="!";
    }
    if (XlfExcel::Instance().excel12() && impl_->Threadsafe_)
    {
        args+="$";
    }

    args+='\0'; // null termination for C string

    LPXLOPER *rgx = new LPXLOPER[10 + nbargs];
    LPXLOPER *px = rgx;
    (*px++) = XlfOper4(dllName.c_str());
    (*px++) = XlfOper4(GetName().c_str());
    (*px++) = XlfOper4(args.c_str());
    (*px++) = XlfOper4(GetAlias().c_str());
    (*px++) = XlfOper4(argnames.c_str());
    (*px++) = XlfOper4(mode_);
    (*px++) = XlfOper4(impl_->category_.c_str());
    (*px++) = XlfOper4("");
    (*px++) = XlfOper4("");
    (*px++) = XlfOper4(GetComment().c_str());
    for (it = arguments.begin(); it != arguments.end(); ++it)
  {
        (*px++) = XlfOper4((*it).GetComment().c_str());
  }
  XLOPER res;
    int err = static_cast<int>(XlfExcel::Instance().Call4v(xlfRegister, &res, 10 + nbargs, rgx));

    if(funcId != NULL)
    {
        *funcId = res.val.num;
    }

    delete[] rgx;
    return err;
}

std::string XlfFuncDesc::argType() const
{
    return XlfExcel::Instance().xlfOperType();
}

std::string XlfFuncDesc4::argType() const
{
    return "P";
}

std::string XlfFuncDesc12::argType() const
{
    return "Q";
}

