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
\file XlfArgDesc.cpp
\brief Implements the XlfArgDesc class.
*/

// $Id$

#include <xlw/XlfArgDesc.h>
#include <xlw/ERR_Macros.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

void XlfArgDesc::CheckNameLength()
{
  ERR_CHECKW2(name_.length() < 19, "argument name \"" << name_.c_str() << "\" may be too long to fit the in the function wizard");
};

XlfArgDesc::XlfArgDesc()
{}

/*!
\param name Name of the argument.
\param comment Help string associated to the argument.
\param type Argument type (defaults to R for XLOPER *). Other argument 
type can be found in Excel documentation under the keyword \e register. 
Note that B stands for double or date, I for 16 bits integer, J for 
32 bits integer. I rarely use the other types.
*/
XlfArgDesc::XlfArgDesc(const std::string& name,
                                const std::string& comment,
                                char type)
    : name_(name), comment_(comment), type_(type)
{ 
  CheckNameLength(); 
}

XlfArgDesc::~XlfArgDesc()
{}

void XlfArgDesc::SetName(const std::string& name)
{ 
  name_ = name; 
  CheckNameLength(); 
}

const std::string& XlfArgDesc::GetName() const
{ 
  return name_; 
}

void XlfArgDesc::SetComment(const std::string& comment)
{ 
  comment_ = comment; 
}

const std::string& XlfArgDesc::GetComment() const
{ 
  return comment_; 
}

char XlfArgDesc::GetType() const
{ 
  return type_; 
}
