// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

/*!
\file XlfFuncDesc.cpp
\brief Implements the XlfFuncDesc class.
*/

// $Id$

#include <xlw/XlfFuncDesc.h>
#include <xlw/XlfArgDescList.h>
#include <xlw/XlfExcel.h>
#include <xlw/ERR_Macros.h>
#include <xlw/XlfException.h>
#include <xlw/XlfOper.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

//! Internal implementation of XlfFuncDesc.
struct XlfFuncDescImpl
{
  //! Ctor.
  XlfFuncDescImpl(const std::string& category): category_(category) {}
  //! Category where the function is displayed in the function wizzard.
  std::string category_;
  //! List of the argument descriptions of the function.
  XlfArgDescList arguments_;
};

/*!
\param name
\param alias 
\param comment The first 3 argument are directly passed to 
XlfAbstractCmdDesc::XlfAbstractCmdDesc.
\param category Category in which the function should appear
in Excel function wizard.
*/
XlfFuncDesc::XlfFuncDesc(const std::string& name, const std::string& alias, const std::string& comment, const std::string& category)
    :XlfAbstractCmdDesc(name, alias, comment), impl_(0)
{
  impl_ = new XlfFuncDescImpl(category);
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

/*!
Registers the function as a function in excel.
\sa XlfExcel, XlfCmdDesc.
*/
int XlfFuncDesc::DoRegister(const std::string& dllName) const
{
  // alias arguments
  XlfArgDescList& arguments = impl_->arguments_;

	size_t nbargs = arguments.size();
	std::string args("R");
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
	args[nbargs + 1] = 0;
	LPXLOPER *rgx = new LPXLOPER[10 + nbargs];
	LPXLOPER *px = rgx;
	(*px++) = XlfOper(dllName.c_str());
	(*px++) = XlfOper(GetName().c_str());
	(*px++) = XlfOper(args.c_str());
	(*px++) = XlfOper(GetAlias().c_str());
	(*px++) = XlfOper(argnames.c_str());
	(*px++) = XlfOper(1.0);
	(*px++) = XlfOper(impl_->category_.c_str());
	(*px++) = XlfOper("");
	(*px++) = XlfOper("");
	(*px++) = XlfOper(GetComment().c_str());
	for (it = arguments.begin(); it != arguments.end(); ++it)
  {
		(*px++) = XlfOper((*it).GetComment().c_str());
  }
	int err = XlfExcel::Instance().Callv(xlfRegister, NULL, 10 + nbargs, rgx);
	delete[] rgx;
	return err;
}

