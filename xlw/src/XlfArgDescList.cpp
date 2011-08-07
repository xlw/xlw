
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte

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
\file XlfArgDescList.cpp
\brief Implements the XlfArgDescList class.
*/

// $Id$

#include <xlw/XlfArgDescList.h>

xlw::XlfArgDescList::XlfArgDescList()
{}

xlw::XlfArgDescList::XlfArgDescList(const XlfArgDescList& list)
{
  arguments_ = list.arguments_;
}

xlw::XlfArgDescList::XlfArgDescList(const XlfArgDesc& first)
{
  arguments_.push_back(first);
}

xlw::XlfArgDescList& xlw::XlfArgDescList::operator+(const XlfArgDesc& newarg)
{
  arguments_.push_back(newarg);
  return *this;
}

xlw::XlfArgDescList::iterator xlw::XlfArgDescList::begin()
{
  return arguments_.begin();
}

xlw::XlfArgDescList::const_iterator xlw::XlfArgDescList::begin() const
{
  return arguments_.begin();
}

xlw::XlfArgDescList::iterator xlw::XlfArgDescList::end()
{
  return arguments_.end();
}

xlw::XlfArgDescList::const_iterator xlw::XlfArgDescList::end() const
{
  return arguments_.end();
}

size_t xlw::XlfArgDescList::size() const
{
  return arguments_.size();
}

xlw::XlfArgDescList xlw::operator+(const xlw::XlfArgDesc& lhs, const xlw::XlfArgDesc& rhs)
{
    return XlfArgDescList(lhs)+rhs;
}

