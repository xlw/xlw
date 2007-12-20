
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
\file XlfOper.inl
\brief Implements inline methods of XlfOper.
*/

// $Id: XlfOper.inl 379 2007-11-16 12:53:30Z ericehlers $

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

/*!
Calls Allocate
*/
INLINE XlfOper::XlfOper()
{
  Allocate();
}

INLINE XlfOper::XlfOper(const XlfOper& oper)
{
  *this = oper;
};

/*!
See XlfOper::Set(double)
*/
INLINE XlfOper::XlfOper(double value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(short)
*/
INLINE XlfOper::XlfOper(short value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(short, bool)
*/
INLINE XlfOper::XlfOper(short value, bool error)
{
  Allocate();
  Set(value, error);
}

/*!
See XlfOper::Set(bool)
*/
INLINE XlfOper::XlfOper(bool value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const char *)
*/
INLINE XlfOper::XlfOper(const char *value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const std::string& value)
*/
INLINE XlfOper::XlfOper(const std::string& value)
{
  Allocate();
  Set(value.c_str());
}

/*!
See XlfOper::Set(const std::wstring& value)
*/
INLINE XlfOper::XlfOper(const std::wstring& value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const CellMatrix&)
*/
INLINE XlfOper::XlfOper(const CellMatrix& value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const MyMatrix&)
*/
INLINE XlfOper::XlfOper(const MyMatrix& value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const MyArray&)
*/
INLINE XlfOper::XlfOper(const MyArray& value)
{
  Allocate();
  Set(value);
}

/*!
See XlfOper::Set(const XlfRef&)

\sa XlfRef
*/
INLINE XlfOper::XlfOper(const XlfRef& range)
{
  Allocate();
  Set(range);
}

/*!
Unlike other XlfOper, the return value is not allocated on the internal
buffer to avoid allocating more memory. Instead it is allocated on a
shared static XLOPER.

\arg error One of the values listed below and defined in xlcall32.h

\code
#define xlerrNull    0      // No info
#define xlerrDiv0    7		// Division by 0
#define xlerrValue   15		// Bad value
#define xlerrRef     23		// Bad reference
#define xlerrName    29		// Bad name
#define xlerrNum     36		// Bad number
#define xlerrNA      42		// Not available
\endcode

\sa XlfOper::SetError(WORD)
*/
INLINE XlfOper XlfOper::Error(WORD xlerr)
{
	//static XLOPER oper;
	//XlfOper ret(&oper);
    // The above is not thread safe.
	XlfOper ret;
	ret.SetError(xlerr);
	return ret;
}

/*!
Forwards to XlfOper::AsDouble.
*/
INLINE int XlfOper::AsInt(int *pxlret) const
{
  return static_cast<int>(AsDouble(pxlret));
}

/*!
Forwards to XlfOper::AsDouble.
*/
INLINE int XlfOper::AsInt(const std::string& ErrorId, int *pxlret) const
{
  return static_cast<int>(AsDouble(ErrorId, pxlret));
}
