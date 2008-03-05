
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers

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
\file XlfAbstractCmdDesc.cpp
\brief Implements the XlfAbstractCmdDesc class.
*/

// $Id$

#include <xlw/XlfAbstractCmdDesc.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfException.h>
//#include <xlw/macros.h>
#include <xlw/defines.h>
#include <iostream>
#include <stdexcept>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

/*!
\param name Name of the command.
\param alias Alias in Excel for the command.
\param comment Help string associated with the comment
*/
xlw::XlfAbstractCmdDesc::XlfAbstractCmdDesc(const std::string& name,
                                       const std::string& alias,
                                       const std::string& comment)
    :name_(name), alias_(alias), comment_(comment)
{}

xlw::XlfAbstractCmdDesc::~XlfAbstractCmdDesc()
{}

/*!
Performs the parts of the Registration that are common to all the subclasses of
XlfAbstractCmdDesc. It then calls the pure virtual method DoRegister for the
subclass dependant parts of the algorithm.
*/
void xlw::XlfAbstractCmdDesc::Register() const
{
  std::string dllName = XlfExcel::Instance().GetName();
  if (dllName.empty())
    throw std::runtime_error("Could not get library name");
  int err = DoRegister(dllName);
  if (err != xlretSuccess)
    std::cerr << XLW__HERE__ << "Error " << err << " while registering " << GetAlias().c_str() << std::endl;
  return;
}

/*!
Performs the parts of the Unregistration that are common to all the subclasses
of XlfAbstractCmdDesc. It then calls the pure virtual method DoUnregister for
the subclass dependent parts of the algorithm.
*/
void xlw::XlfAbstractCmdDesc::Unregister() const
{
  std::string dllName = XlfExcel::Instance().GetName();
  if (dllName.empty())
    throw std::runtime_error("Could not get library name");
  int err = DoUnregister(dllName);
  if (err != xlretSuccess)
    std::cerr << XLW__HERE__ << "Error " << err << " while registering " << GetAlias().c_str() << std::endl;
  return;
}

void xlw::XlfAbstractCmdDesc::SetName(const std::string& name)
{
  name_ = name;
}

const std::string& xlw::XlfAbstractCmdDesc::GetName() const
{
  return name_;
}

void xlw::XlfAbstractCmdDesc::SetAlias(const std::string& alias)
{
  alias_ = alias;
}

const std::string& xlw::XlfAbstractCmdDesc::GetAlias() const
{
  return alias_;
}

void xlw::XlfAbstractCmdDesc::SetComment(const std::string& comment)
{
  comment_ = comment;
}

const std::string& xlw::XlfAbstractCmdDesc::GetComment() const
{
  return comment_;
}

/*!
The new arguments overwrite any existing ones that have previously been set.
You cannot push back the arguments one by one.
*/
void xlw::XlfAbstractCmdDesc::SetArguments(const XlfArgDescList& arguments)
{
  arguments_ = arguments;
}

const xlw::XlfArgDescList& xlw::XlfAbstractCmdDesc::GetArguments() const
{
  return arguments_;
}

