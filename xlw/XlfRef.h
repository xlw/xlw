// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfRef_H
#define INC_XlfRef_H

/*!
\file XlfRef.h
\brief Declares the XlfRef class.
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>

#if defined(_MSC_VER)
#pragma once
#endif

// Forward declaration.
//! Wrapper around XLOPER Excel data type.
class EXCEL32_API XlfOper;

//! Encapsulate a range of cells.
/*!
A range is actually a reference to a range of cells in the spreadsheet.
This range is stored as an absolute reference even if you can access
the elements relatively to the upper left corner of the range (starting
at 0 to number of row/column minus 1).

The dtor, copy ctor and assignment otor are generated by the compiler.

\bug You cannot use a ref as an output.

\warning Note that the Excel API is limited to the first 256 columns
This class hold a reference to a single range in a single spreadsheet.
It is intended to be a helper class to refer range through XlfOper.
*/
class EXCEL32_API XlfRef
{
public:
  //! Default ctor.
  XlfRef();
  //! Absolute reference ctor.
  XlfRef(WORD top, BYTE left, WORD bottom, BYTE right);
  //! Absolute reference ctor, to a single cell.
  XlfRef(WORD row, BYTE col);
  //! Get the first row of the range (0 based).
  WORD GetRowBegin() const;
  //! Get passed the last row of the range (0 based).
  WORD GetRowEnd() const;
  //! Get the first column of the range (0 based).
  BYTE GetColBegin() const;
  //! Get passed the last column of the range (0 based).
  BYTE GetColEnd() const;
  //! Get the number of columns.
  BYTE GetNbCols() const;
  //! Get the number of rows.
  WORD GetNbRows() const;
  //! Set the first row of the range.
  void SetRowBegin(WORD rowbegin);
  //! Set passed the last row of the range.
  void SetRowEnd(WORD rowend);
  //! Set the first column of the range.
  void SetColBegin(BYTE colbegin);
  //! Set passed the last column of the range.
  void SetColEnd(BYTE colend);
  //! Access operator
  XlfOper operator()(WORD relativerow, BYTE relativecol) const;

private:
  //! Index of the top row of the range reference.
  WORD rowbegin_;
  //! Index of one past the last row of the range reference.
  WORD rowend_;
  //! Index of the left most column of the range reference.
  BYTE colbegin_;
  //! Index of one past the right most column of the range reference.
  BYTE colend_;
};

#ifdef NDEBUG
#include <xlw/XlfRef.inl>
#endif

#endif