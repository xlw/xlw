// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfOper_H
#define INC_XlfOper_H

/*!
\file XlfOper.h
\brief Declares class XlfOper.
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <windows.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

class XlfRef;

//! Wrapper around a pointer to the XLOPER Excel data structure.
/*!
This class eases the work of marchalling and unmarshalling data to 
the Excel XLOPER format (including memory).

XlfOper holds a pointer to a XLOPER.

\warning It is important \e not to add any data member to this class 
because the library heavily relies on the fact that LPXLOPER and 
XlfOper have the same size. It allows the library to interpret any 
LPXLOPER sent by Excel as a XlfOper.
*/
class EXCEL32_API XlfOper
{
public:
  //! Default ctor.
  XlfOper();
  //! Copy ctor.
  XlfOper(const XlfOper& oper);
  //! XLOPER * ctor.
  XlfOper(LPXLOPER lpxloper, bool isExcelData = true);
  //! double ctor.
  XlfOper(double value);
  //! short ctor.
  XlfOper(short value);
  //! boolean ctor.
  XlfOper(bool value);
  //! 0 terminated chararcter string ctor.
  XlfOper(const char *value);
  //! XlfRef ctor.
  XlfOper(const XlfRef& range);
#ifndef PORT_NO_MEMBER_TEMPLATE
  //! Container ctor.
  template <class FwdIt>
  XlfOper(WORD rows, BYTE cols, FwdIt start)
#ifdef PORT_PARTIAL_MEMBER_TEMPLATE
  { 
    Allocate(); 
    Set(rows,cols,start); 
  }
#else
;
#endif
#endif
  //! Dtor
  ~XlfOper();
  //! Free auxiliary memory associated with the XLOPER
  void FreeAuxiliaryMemory() const;
  //! Assignment operator
  XlfOper& operator=(const XlfOper& xloper);

  //! Is the data missing ?
  bool IsMissing() const;
  //! Is the data an error ?
  bool IsError() const;
  //! Converts to a double.
  double AsDouble() const;
  //! Converts to a short.
  short AsShort() const;
  //! Converts to a bool.
  bool AsBool() const;
  //! Converts to an int.
  int AsInt() const;
  //! Converts to a char *.
  char * AsString() const;
  //! Converts to a XlfReg.
  XlfRef AsRef() const;
  //! Gets the internal LPXLOPER.
  LPXLOPER GetLPXLOPER() const;

  //! Set the underlying XLOPER * to lpxloper
  XlfOper& Set(LPXLOPER lpxloper);
  //! Set to a a double
  XlfOper& Set(double value);
  //! Set to a a short
  XlfOper& Set(short value);
  //! Set to a a boolean
  XlfOper& Set(bool value);
  //! Set to a a zero-terminated character string
  XlfOper& Set(const char *value);
  //! Set to a range
  XlfOper& Set(const XlfRef& range);
  //! Set to an error value
  XlfOper& SetError(WORD error);
  //! Cast to XLOPER *
  operator LPXLOPER();
#ifndef PORT_NO_MEMBER_TEMPLATE
  //! Set to an array
  /*! 
  \param r number of rows in the array
  \param c number of columns in the array
  \param it iterator pointing to the begining of a container
    of size r x c (at least) that contain the data.
  \warning Data are to be stored row-wise.
  */
  template<class FwdIt>
  XlfOper& Set(WORD r, BYTE c, FwdIt it)
#ifdef PORT_PARTIAL_MEMBER_TEMPLATE
  {
    lpxloper_->xltype = xltypeMulti;
    lpxloper_->val.array.rows = r;
    lpxloper_->val.array.columns = c;
    lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
    for (size_t i = 0; i < size_t(r*c); ++i, ++it)
      lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
    return *this;
  }
#else
  ;
#endif
#endif

private:
  //! Internal LPXLOPER.
  LPXLOPER lpxloper_;

  //! Coerces method is called by conversion operators if needed (never by the user).
  void Coerce(short type, XlfOper& res) const;

  //! Reserves memory in XLL buffer (garbage collected).
  void Allocate();
  
  //! Anticipates deallocation if possible.
  void Deallocate();
};

#ifdef PORT_NO_MEMBER_TEMPLATE
/*!
\brief Set an array to an XlfOper.
Because not all compilers support member template this function
is provided in order to replace the template method Set(WORD,BYTE,FwdIt).
*/
template <class FwdIt>
XlfOper& XlfOperSet(XlfOper& oper, WORD rows, BYTE cols, FwdIt it)
{
LPXLOPER lpxloper=oper;
lpxloper->xltype = xltypeMulti;
lpxloper->val.array.rows = rows;
lpxloper->val.array.columns = cols;
lpxloper->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(rows*cols*sizeof(XLOPER));
for (size_t i = 0; i < rows*cols; ++i, ++it)
lpxloper->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
return oper;
}
#else
#ifndef PORT_PARTIAL_MEMBER_TEMPLATE
/*!
\param r number of rows in the array
\param c number of columns in the array
\param it iterator pointing to the begining of a container
of size r x c (at least) that contain the data.
\warning Data are to be stored row-wise.
*/
template<class FwdIt>
XlfOper& XlfOper::Set<FwdIt>(WORD r, BYTE c, FwdIt it);
{
  lpxloper_->xltype = xltypeMulti;
  lpxloper_->val.array.rows = r;
  lpxloper_->val.array.columns = c;
  lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
  for (size_t i = 0; i < r*c; ++i, ++it)
    lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
  return *this;
}
#endif
#endif

#ifdef NDEBUG
#include <xlw/XlfOper.inl>
#endif

#endif