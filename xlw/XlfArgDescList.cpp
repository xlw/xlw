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
\file XlfArgDescList.cpp
\brief Implements the XlfArgDescList class.
*/

// $Id$

#include <xlw/XlfArgDescList.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

XlfArgDescList::XlfArgDescList()
{}

XlfArgDescList::XlfArgDescList(const XlfArgDescList& list)
{ 
  arguments_ = list.arguments_; 
}

XlfArgDescList::XlfArgDescList(const XlfArgDesc& first)
{
  arguments_.push_back(first); 
}

XlfArgDescList& XlfArgDescList::operator+(const XlfArgDesc& newarg)
{ 
  arguments_.push_back(newarg); 
  return *this; 
}

XlfArgDescList::iterator XlfArgDescList::begin()
{ 
  return arguments_.begin(); 
}

XlfArgDescList::const_iterator XlfArgDescList::begin() const
{ 
  return arguments_.begin(); 
}

XlfArgDescList::iterator XlfArgDescList::end()
{ 
  return arguments_.end(); 
}

XlfArgDescList::const_iterator XlfArgDescList::end() const
{ 
  return arguments_.end(); 
}

size_t XlfArgDescList::size() const
{ 
  return arguments_.size(); 
}

XlfArgDescList operator+(const XlfArgDesc& lhs, const XlfArgDesc& rhs)
{
  return XlfArgDescList(lhs)+rhs;
}