/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte

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
\file XlfOper.cpp
\brief Implements the XlfOper class.
*/

// $Id$

#include <xlw/XlfOper.h>
#include <xlw/ERR_Macros.h>
#include <xlw/XlfException.h>
#include <xlw/XlfRef.h>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfOper.inl>
#endif

#if !defined(PORT_USE_OLD_IO_HEADERS)
PORT_USING_NAMESPACE(std);
#endif

/*!
This bit is currently unused by Microsoft Excel. We set it
to indicate that the LPXLOPER (passed by Excel) holds some extra
memory to be freed.

This bit is controled in ~XlfOper to know if the DLL should release
auxiliary memory or not by a call to FreeAuxiliaryMemory.
*/
int xlbitCallFreeAuxMem = 0x8000;

/*!
Shallow copy of a pointer to XLOPER.
\param lpxloper Pointer to XLOPER.
\param isExcelData Flags that tells if the auxiliary data is allocated by
Excel or by the XLL (default is true).
*/
XlfOper::XlfOper(LPXLOPER lpxloper, bool isExcelData): lpxloper_(lpxloper)
{
  if (lpxloper_ == 0)
	return;

  int type = lpxloper_->xltype;
  bool isAuxType = (type == xltypeStr || type == xltypeRef ||
                	type == xltypeMulti || type == xltypeBigData);
  if (isExcelData && isAuxType)
  {
    lpxloper_->xltype&=xlbitCallFreeAuxMem;
  }
  return;
}

/*!
Calls Deallocate() to free the XLOPER allocated by the XLL. XLOPER allocated
by Excel remain under Excel responsability.

Calls FreeAuxiliaryMemory if the XLOPER is owned by Excel and maintains heap
allocated data. If it is not owned by Excel, the data is assumed to be deleted
elsewhere in the XLL.
*/
XlfOper::~XlfOper()
{
  if (! lpxloper_)
	  return;

  if (lpxloper_->xltype & xlbitCallFreeAuxMem)
  {
    FreeAuxiliaryMemory();
    // and switch back the bit as it was originally
    lpxloper_->xltype&=xlbitCallFreeAuxMem;
  }
  Deallocate();
  return;
}

/*!
Allocates 16 bits (size of a XLOPER) on the temporary buffer
stored by XlfExcel with a call to XlfExcel::GetMemory().

\warning Each XlfOper allocation causes a call to Allocate which in turn
reserve the necessary number of bytes in the internal buffer. The
problem is that even temporary XlfOper used inside the xll function use
this internal buffer. This buffer is not freed before the next call to
the xll to ensure Excel can use the data before they are freed. This
causes a bottleneck if the function uses many temporary XlfOper (see
Deallocate()).

\return \c xlretSuccess or \c xlretInvXloper if no memory is could 
be allocated.
*/
int XlfOper::Allocate()
{
  lpxloper_ = (LPXLOPER)XlfExcel::Instance().GetMemory(sizeof(XLOPER));
  if (!lpxloper_)
    return xlretInvXloper;
  lpxloper_->xltype = xltypeNil;
  return xlretSuccess;
}

void XlfOper::FreeAuxiliaryMemory() const
{
  int err = XlfExcel::Instance().XlfExcel::Instance().Call(xlFree, NULL, 1, (LPXLOPER)lpxloper_);
  ERR_CHECKW(err == xlretSuccess,"Call to xlFree failed");
  return;
}

/*!
\param type is an integer indicating the target type we want to coerce to.
\param result is the XLOPER where to store the output.

\todo Optimize xlType to avoid consuming the buffer.
*/
int XlfOper::Coerce(short type, XlfOper& result) const
{
  XlfOper xlType(type);
  int xlret = XlfExcel::Instance().Call(xlCoerce, (LPXLOPER)result, 2, (LPXLOPER)lpxloper_, (LPXLOPER)xlType);
  return xlret;
}

double XlfOper::AsDouble() const
{
	double d;
	int xlret = ConvertToDouble(d);
	XlfExcel::Instance().ThrowOnCriticalError(xlret);
	return d;
};

int XlfOper::ConvertToDouble(double& d) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
	  return xlretInvXloper;

  if (lpxloper_->xltype == xltypeInt)
  {
	  d = lpxloper_->val.w;
      xlret=xlretSuccess;
  }
  else if (lpxloper_->xltype == xltypeNum)
  {
	  d = lpxloper_->val.num;
      xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp,false);
    // Coerces to numeric type.
    xlret = Coerce(xltypeNum,cast);
	if (xlret == xlretSuccess)
	    xlret = cast.ConvertToDouble(d);
  }
  return xlret;
};

short XlfOper::AsShort() const
{
	short s;
	int xlret = ConvertToShort(s);
	XlfExcel::Instance().ThrowOnCriticalError(xlret);
	return s;
};

int XlfOper::ConvertToShort(short& s) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
	  return xlretInvXloper;

  if (lpxloper_->xltype == xltypeNum)
  {
	  s = lpxloper_->val.num;
      xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp,false);
    // Coerces to numeric type.
    xlret = Coerce(xltypeNum,cast);
	if (xlret == xlretSuccess)
	    xlret = cast.ConvertToShort(s);
  }
  return xlret;
};


bool XlfOper::AsBool() const
{
	bool b;
	int xlret = ConvertToBool(b);
	XlfExcel::Instance().ThrowOnCriticalError(xlret);
	return b;
};

int XlfOper::ConvertToBool(bool& b) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
	  return xlretInvXloper;

  if (lpxloper_->xltype == xltypeBool)
  {
	  b = (lpxloper_->val.boolean != 0);
	  xlret = xlretSuccess;
  }
  else
  {
    // see ConvertToDouble
    XLOPER tmp;
    XlfOper cast(&tmp,false);
    xlret = Coerce(xltypeBool,cast);
	if (xlret == xlretSuccess)
		xlret = cast.ConvertToBool(b);
  }
  return xlret;
};

/*!
For character strings, the XLL allocates
the memory on its own buffer. This buffer is automatically freed
when a function of the XLL is called again. Note that coerce to
a char string is the slowest cast of all.
*/
char * XlfOper::AsString() const
{
	char * s;
	int xlret = ConvertToString(s);
	XlfExcel::Instance().ThrowOnCriticalError(xlret);
	return s;
};

int XlfOper::ConvertToString(char *& s) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
	  return xlretInvXloper;

  if (lpxloper_->xltype == xltypeStr)
  {
    size_t n = lpxloper_->val.str[0];
    s = XlfExcel::Instance().GetMemory(n + 1);
    memcpy(s, lpxloper_->val.str + 1, n);
    s[n] = 0;
	xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER tmp;
	// Second argument true marks XlfOper so that xlFree is called on the
	// MS Excel allocated memory (the string) when XlfOper goes out of scope.
    XlfOper cast(&tmp,true);
    xlret = Coerce(xltypeStr,cast);
	if (xlret == xlretSuccess)
	    xlret = cast.ConvertToString(s);
  }
  return xlret;
}

XlfRef XlfOper::AsRef() const
{
	XlfRef r;
	int xlret = ConvertToRef(r);
	XlfExcel::Instance().ThrowOnCriticalError(xlret);
	return r;
}

int XlfOper::ConvertToRef(XlfRef& r) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
	  return xlretInvXloper;

  if (lpxloper_->xltype == xltypeRef)
  {
	const XLREF& ref=lpxloper_->val.mref.lpmref->reftbl[0];
    r = XlfRef (ref.rwFirst,  // top
                ref.colFirst, // left
                ref.rwLast,   // bottom
                ref.colLast,  // right
				lpxloper_->val.mref.idSheet); // sheet id
	xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER tmp;
	// Second argument true marks XlfOper so that xlFree is called on the
	// MS Excel allocated memory (the reference array) when XlfOper goes 
	// out of scope.
    XlfOper cast(&tmp,true);
    xlret = Coerce(xltypeRef,cast);
	if (xlret == xlretSuccess)
	    xlret = cast.ConvertToRef(r);
  }
  return xlret;
}

XlfOper& XlfOper::Set(LPXLOPER lpxloper)
{
  ERR_CHECKX2(lpxloper != 0, XlfException,"Assignment of NULL pointer");
  lpxloper_ = lpxloper;
  return *this;
}

XlfOper& XlfOper::Set(double value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeNum;
    lpxloper_->val.num = value;
  }
  return *this;
}

XlfOper& XlfOper::Set(short value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeInt;
    lpxloper_->val.w = value;
  }
  return *this;
}

XlfOper& XlfOper::Set(bool value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeBool;
    lpxloper_->val.boolean = value;
  }
  return *this;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the XlfRef is not copied.
*/
XlfOper& XlfOper::Set(const XlfRef& range)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeRef;
    XLMREF * pmRef = reinterpret_cast<XLMREF *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF)));
	// if no memory is available
	if (pmRef == 0)
	{
		// set XlfOper to an invalid state
		lpxloper_=0;
	}
	else
	{
      pmRef->count=1;
      pmRef->reftbl[0].rwFirst = range.GetRowBegin();
      pmRef->reftbl[0].rwLast = range.GetRowEnd()-1;
      pmRef->reftbl[0].colFirst = range.GetColBegin();
      pmRef->reftbl[0].colLast = range.GetColEnd()-1;
      lpxloper_->val.mref.lpmref = pmRef;
      lpxloper_->val.mref.idSheet = range.GetSheetId();
	}
  }
  return *this;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the string is not copied.

\note String longer than 255 characters are truncated. A warning
is issued in debug mode.
*/
XlfOper& XlfOper::Set(const char *value)
{
  if (lpxloper_)
  {
	lpxloper_->xltype = xltypeStr;
	int n = strlen(value);
    ERR_CHECKW2(n<256,"String too long will be truncated");
    // One byte more for NULL terminal char (allow use of strcpy)
    // and one for the std::string size (convention used by Excel)
    LPSTR str = reinterpret_cast<LPSTR>(XlfExcel::Instance().GetMemory(n + 2));
	if (str == 0)
	{
		lpxloper_=0;
	}
	else
	{
      strcpy(str + 1, value);
      // the number of character include the final \0 or not ?
      lpxloper_->val.str = str;
      lpxloper_->val.str[0] = (BYTE)(n + 1);
	}
  }
  return *this;
}

XlfOper& XlfOper::SetError(WORD error)
{
  if (lpxloper_)
  {
	lpxloper_->xltype = xltypeErr;
	lpxloper_->val.err = error;
  }
  return *this;
}

