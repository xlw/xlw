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
\file XlfRef.cpp
\brief Implements the XlfRef class.
*/

#include "XlfRef.h"
#include "XlfOper.h"
#include "ERR_Macros.h"
#include "XlfException.h"

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

#ifndef NDEBUG
#include "XlfRef.inl"
#endif

XlfOper XlfRef::operator()(WORD r, BYTE c) const
{
	ERR_CHECKX(rowbegin_ + r<rowend_ && colbegin_ + c<colend_, XlfException,"access out of range");
	XlfOper res;
	res.Set(XlfRef(rowbegin_ + r, colbegin_ + c));
	return res;
}
