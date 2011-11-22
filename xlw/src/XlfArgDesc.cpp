
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
\file XlfArgDesc.cpp
\brief Implements the XlfArgDesc class.
*/

// $Id$

#include <xlw/XlfArgDesc.h>
#include <xlw/XlfExcel.h>
#include <iostream>
#include <xlw/macros.h>

void xlw::XlfArgDesc::CheckNameLength()
{
    if (name_.length() >= 19)
        std::cerr << XLW__HERE__ << "Argument name \"" << name_.c_str()
        << "\" may be too long to fit the in the function wizard" << std::endl;
};

xlw::XlfArgDesc::XlfArgDesc()
{}

/*!
\param name Name of the argument.
\param comment Help string associated to the argument.
\param type Argument type  - The type defaults to the XLOPER type corresponding
to the version (4 or 12) of the running instance of Excel.
*/
xlw::XlfArgDesc::XlfArgDesc(const std::string& name,
                       const std::string& comment,
                       const std::string& type)
    : name_(name), comment_(comment), type_(type)
{
    CheckNameLength();
}

xlw::XlfArgDesc::~XlfArgDesc()
{}

void xlw::XlfArgDesc::SetName(const std::string& name)
{
    name_ = name;
    CheckNameLength();
}

const std::string& xlw::XlfArgDesc::GetName() const
{
    return name_;
}

void xlw::XlfArgDesc::SetComment(const std::string& comment)
{
    comment_ = comment;
}

const std::string& xlw::XlfArgDesc::GetComment() const
{
    return comment_;
}

std::string xlw::XlfArgDesc::GetType() const
{
    if (type_ == "XLF_OPER") {
        return XlfExcel::Instance().xlfOperType();
    } else if (type_ == "XLF_XLOPER") {
        return XlfExcel::Instance().xlfXloperType();
    } else if (type_ == "XLW_WSTR") {
        return XlfExcel::Instance().wStrType();
    } else if (type_ == "XLW_FP") {
        return XlfExcel::Instance().fpType();
    } else {
        return type_;
    }
}

