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
\file XlfOper.cpp
\brief Implements the XlfOper class.
*/

// $Id$

#include <xlw/XlfOper.h>
#include <xlw/xlcall32.h>
#include <xlw/XlfExcel.h>
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
  if (isExcelData && lpxloper->xltype == xltypeStr)
    lpxloper_->xltype&=xlbitCallFreeAuxMem;
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
 
\bug Each XlfOper allocation causes a call to Allocate which in turn
reserve the necessary number of bytes in the internal buffer. The 
problem is that even temporary XlfOper used inside the xll function use 
this internal buffer. This buffer is not freed before the next call to 
the xll to ensure Excel can use the data before they are freed. This
causes a bottleneck if the function uses many temporary XlfOper (see 
Deallocate()).
*/
void XlfOper::Allocate()
{
  lpxloper_ = (LPXLOPER)XlfExcel::Instance().GetMemory(sizeof(XLOPER));
  if (!lpxloper_)
    return;
  lpxloper_->xltype = xltypeNil;
  return;
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
*/
void XlfOper::Coerce(short type, XlfOper& result) const
{
  int err = XlfExcel::Instance().Call(xlCoerce, (LPXLOPER)result, 2, (LPXLOPER)lpxloper_, (LPXLOPER)XlfOper(type));
  if (err != xlretSuccess)
    ERR_THROW(XlfExceptionCoerce);
}

double XlfOper::AsDouble() const
{
  if (lpxloper_->xltype != xltypeInt && lpxloper_->xltype != xltypeNum)
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp,false);
    // Coerces to numeric type.
    Coerce(xltypeNum,cast);
    // Returns the value.
    return cast.AsDouble();
  }
  if (lpxloper_->xltype == xltypeInt)
    return double(lpxloper_->val.w);
  return double(lpxloper_->val.num);
};

short XlfOper::AsShort() const
{
  if (lpxloper_->xltype != xltypeInt && lpxloper_->xltype != xltypeNum)
  {
    // see AsDouble
    XLOPER tmp;
    XlfOper cast(&tmp,false);
    Coerce(xltypeInt,cast);
    return cast.AsShort();
  }
  if (lpxloper_->xltype == xltypeNum)
    return short(lpxloper_->val.num);
  return short(lpxloper_->val.w);
};

bool XlfOper::AsBool() const
{
  if (lpxloper_->xltype != xltypeBool)
  {
    // see AsDouble
    XLOPER tmp;
    XlfOper cast(&tmp,false);
    Coerce(xltypeBool,cast);
    return cast.AsBool();
  }
  return bool(lpxloper_->val.boolean != 0);
};

/*!
For character strings, the XLL allocates 
the memory on its own buffer. This buffer is automatically freed 
when a function of the XLL is called again. Note that coerce to 
a char string is the slowest cast of all.
*/
char * XlfOper::AsString() const
{
  if (lpxloper_->xltype != xltypeStr)
  {
    // see AsDouble
    XLOPER tmp;
    XlfOper cast(&tmp,true);
    Coerce(xltypeStr,cast);
    char *res = cast.AsString();
    return res;
  }
  size_t n = lpxloper_->val.str[0];
  char *res = XlfExcel::Instance().GetMemory(n + 1);
  memcpy(res, lpxloper_->val.str + 1, n);
  res[n] = 0;
  return res;
};

XlfRef XlfOper::AsRef() const
{
  if (lpxloper_->xltype != xltypeSRef)
  {
    // see AsDouble
    XLOPER tmp;
    XlfOper cast(&tmp,false);
    Coerce(xltypeSRef,cast);
    return cast.AsRef();
  }
  return XlfRef(lpxloper_->val.sref.ref.rwFirst,  // top
                lpxloper_->val.sref.ref.colFirst, // left
                lpxloper_->val.sref.ref.rwLast,   // bottom
                lpxloper_->val.sref.ref.colLast); // right
}


XlfOper& XlfOper::Set(LPXLOPER lpxloper)
{
  ERR_CHECKX2(lpxloper != 0, XlfException,"Assignment of NULL pointer");
  lpxloper_ = lpxloper;
  return *this;
}

XlfOper& XlfOper::Set(double value)
{
  lpxloper_->xltype = xltypeNum;
  lpxloper_->val.num = value;
  return *this;
}

XlfOper& XlfOper::Set(short value)
{
  lpxloper_->xltype = xltypeInt;
  lpxloper_->val.w = value;
  return *this;
}

XlfOper& XlfOper::Set(bool value)
{
  lpxloper_->xltype = xltypeBool;
  lpxloper_->val.boolean = value;
  return *this;
}

XlfOper& XlfOper::Set(const XlfRef& range)
{
  lpxloper_->xltype = xltypeSRef;
  lpxloper_->val.sref.ref.rwFirst = range.GetRowBegin();
  lpxloper_->val.sref.ref.rwLast = range.GetRowEnd()-1;
  lpxloper_->val.sref.ref.colFirst = range.GetColBegin();
  lpxloper_->val.sref.ref.colLast = range.GetColEnd()-1;
  return *this;
}

/*!
\bug String longer than 255 characters are truncated. A warning
is issued in debug mode.
*/
XlfOper& XlfOper::Set(const char *value)
{
  lpxloper_->xltype = xltypeStr;
  int n = strlen(value);
  ERR_CHECKW2(n<256,"String too long will be truncated");
  // One byte more for NULL terminal char (allow use of strcpy)
  // and one for the std::string size (convention used by Excel)
  lpxloper_->val.str = (LPSTR)XlfExcel::Instance().GetMemory(n + 2);
  strcpy(lpxloper_->val.str + 1, value);
  // the number of character include the final \0 or not ?
  lpxloper_->val.str[0] = (BYTE)(n + 1);
  return *this;
}

XlfOper& XlfOper::SetError(WORD error)
{
  lpxloper_->xltype = xltypeErr;
  lpxloper_->val.err = error;
  return *this;
}

