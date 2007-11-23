
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
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
\file XlfOperImpl.inl
\brief Implements inline methods of XlfOperImpl.
*/

// $Id: XlfOperImpl.inl 379 2007-11-16 12:53:30Z ericehlers $

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

/*!
Calls Allocate
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion) const
{
  Allocate(xlfOperUnion);
}

/*!
See XlfOper::Set(xlfOperUnion, double)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, double value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, short)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, short value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, short, bool)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, short value, bool error) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value, error);
}

/*!
See XlfOper::Set(xlfOperUnion, bool)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, bool value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const char *)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const char *value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const std::string& value)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const std::string& value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value.c_str());
}

/*!
See XlfOper::Set(xlfOperUnion, const std::wstring& value)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const std::wstring& value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const CellMatrix&)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const CellMatrix& value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const MyMatrix&)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const MyMatrix& value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const MyArray&)
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const MyArray& value) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, value);
}

/*!
See XlfOper::Set(xlfOperUnion, const XlfRef&)

\sa XlfRef
*/
INLINE void XlfOperImpl::Init(XlfOperUnion &xlfOperUnion, const XlfRef& range) const
{
  Allocate(xlfOperUnion);
  Set(xlfOperUnion, range);
}

/*!
Forwards to XlfOper::AsDouble.
*/
INLINE int XlfOperImpl::AsInt(XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  return static_cast<int>(AsDouble(xlfOperUnion, pxlret));
}

/*!
Forwards to XlfOper::AsDouble.
*/
INLINE int XlfOperImpl::AsInt(XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  return static_cast<int>(AsDouble(xlfOperUnion, ErrorId, pxlret));
}
