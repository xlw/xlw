// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

/*!
\file XlfAbstractCmdDesc.cpp
\brief Implements the XlfAbstractCmdDesc class.
*/

#include "XlfAbstractCmdDesc.h"
#include "XlfExcel.h"
#include "ERR_Macros.h"
#include "XlfException.h"

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

/*!
\param name Name of the command.
\param alias Alias in Excel for the command.
\param comment Help string associated with the comment
*/
XlfAbstractCmdDesc::XlfAbstractCmdDesc(const std::string& name,
                                              const std::string& alias,
                                              const std::string& comment)
    :name_(name), alias_(alias), comment_(comment)
{}

XlfAbstractCmdDesc::~XlfAbstractCmdDesc()
{}

/*!
Performs the parts of the Registration that are common to a registration
of all the subclasses of XlfAbstractCmdDesc. It then calls the pure 
virtual method DoRegister for the subclass dependant parts of the 
algorithm.
*/
void XlfAbstractCmdDesc::Register() const
{
	std::string dllName = XlfExcel::Instance().GetName();
	ERR_CHECKX2(!dllName.empty(), XlfException,"Library name is not initialized")
  int err = DoRegister(dllName);
	ERR_CHECKW(err == xlretSuccess,"error " << err << " while registering " << GetAlias().c_str());
  return;
}

void XlfAbstractCmdDesc::Unregister()
{ 
  return; 
}

void XlfAbstractCmdDesc::SetName(const std::string& name)
{
  name_ = name;
}

const std::string& XlfAbstractCmdDesc::GetName() const
{
  return name_;
}

void XlfAbstractCmdDesc::SetAlias(const std::string& alias)
{
  alias_ = alias;
}

const std::string& XlfAbstractCmdDesc::GetAlias() const
{
  return alias_;
}

void XlfAbstractCmdDesc::SetComment(const std::string& comment)
{
  comment_ = comment;
}

const std::string& XlfAbstractCmdDesc::GetComment() const
{
  return comment_;
}

