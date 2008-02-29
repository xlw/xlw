
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfOper12_H
#define INC_XlfOper12_H

/*!
\file XlfOper12.h
\brief Declares class XlfOper12.
*/

// $Id: XlfOper12.h 340 2007-10-14 15:40:31Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfRef.h>
#include <xlw/MyContainers.h>
#include <vector>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//class XlfRef;
class CellMatrix;

//! Wrapper around a pointer to the XLOPER Excel data structure.
/*!
This class eases the work of marchalling and unmarshalling data to
the Excel XLOPER format (including memory).

XlfOper12 holds a pointer to a XLOPER.

\warning It is important \e not to add any data member to this class
because the library heavily relies on the fact that LPXLOPER12 and
XlfOper12 have the same size. It allows the library to interpret any
LPXLOPER12 sent by Excel as a XlfOper12.
*/
class EXCEL32_API XlfOper12
{
public:
  //! Default ctor.
  XlfOper12();
  //! Copy ctor.
  XlfOper12(const XlfOper12& oper);
  //! XLOPER * ctor.
  XlfOper12(LPXLOPER12 lpxloper);
  //! double ctor.
  XlfOper12(double value);
  //! short ctor.
  XlfOper12(short value);
  //! short or error ctor.
  XlfOper12(short value, bool Error);
  //! boolean ctor.
  XlfOper12(bool value);
  //! 0 terminated chararcter string ctor.
  XlfOper12(const char *value);
  //!  string ctor.
  XlfOper12(const std::string& value);
  //!  wstring ctor.
  XlfOper12(const std::wstring& value);
  //! CellMatrix ctor.
  XlfOper12(const CellMatrix& value);
  //! MyMatrix ctor.
  XlfOper12(const MyMatrix& value);
  //! MyArray ctor.
  XlfOper12(const MyArray& value);
  //! XlfRef ctor.
  XlfOper12(const XlfRef& range);
  //! Container ctor.
  template <class FwdIt>
  XlfOper12(WORD rows, BYTE cols, FwdIt start)
  {
    Allocate();
    Set(rows,cols,start);
  }
  //! Constructs an Excel error.
  static XlfOper12 Error(WORD);
  //! Dtor
  ~XlfOper12();
  //! Free auxiliary memory associated with the XLOPER
  void FreeAuxiliaryMemory() const;
  //! Assignment operator
  XlfOper12& operator=(const XlfOper12& xloper);

  //! Is the data missing ?
  bool IsMissing() const;
  //! Is the data an error ?
  bool IsError() const;
  //! Is the data a reference ?
  bool IsRef() const;
  //! Is the data a sheet reference ?
  bool IsSRef() const;
  //! Is the data an array ?
  bool IsMulti() const;
  //! Is the data a number ?
  bool IsNumber() const;
  //! Is the data a string ?
  bool IsString() const;
  //! Is the data a null value ?
  bool IsNil() const;
  //! Is the data a boolean ?
  bool IsBool() const;
  //! Is the data an integer ?
  bool IsInt() const;

  //! Converts to a double.
  double AsDouble(int * pxlret = 0) const;
 //! Converts to a double with error identifer.
  double AsDouble(const std::string& ErrorId, int * pxlret = 0) const;

  //! Lets the user choose how to convert a range in a vector<double>
  /*!
   * Default policy is UniDimensional. The 2 others are typically to facilitate conversion
   * to matrix classes.
   *
   * \sa ConvertToDoubleVector, AsDoubleVector.
   */
  enum DoubleVectorConvPolicy
  {
    /*! Generates an error if the range is not uni dimensional (one row or one column). */
    UniDimensional,
    /*! Flattens the range in a C-like way (rows are continuous). */
    RowMajor,
    /*! Flattens the range in a Fortran-like way (columns are continuous). */
    ColumnMajor
  };

  //! Converts to a std::vector<double>.
  std::vector<double> AsDoubleVector(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
  std::vector<double> AsDoubleVector(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;

  //! Converts to an array.
  MyArray AsArray(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
  MyArray AsArray(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;

  //! Converts to a short.
  short AsShort(int * pxlret = 0) const;
 //! Converts to a short with error identifer.
  short AsShort(const std::string& ErrorId, int * pxlret = 0) const;

  //! Converts to a bool.
  bool AsBool(int * pxlret = 0) const;
  //! Converts to a bool with error identifer.
  bool AsBool(const std::string& ErrorId,int * pxlret = 0) const;

  //! Converts to an int.
  int AsInt(int * pxlret = 0) const;
 //! Converts to an int with error identifer.
  int AsInt(const std::string& ErrorId,int * pxlret = 0) const;

  //! Converts to a char *.
  char * AsString(int * pxlret = 0) const;
 //! Converts to a char * with error identifer.
  char * AsString(const std::string& ErrorId,int * pxlret = 0) const;
  //! Converts to a wstring.
  std::wstring AsWstring(int * pxlret = 0) const;

  //! Converts to a cell Matrix.
  CellMatrix AsCellMatrix( int * pxlret=0) const;
  //! Converts to a cell Matrix with error identifer.
  CellMatrix AsCellMatrix( const std::string& ErrorId,int * pxlret=0) const;

  //! Converts to a matrix.
  MyMatrix AsMatrix( int * pxlret=0) const;
  //! Converts to a matrix with error identifer.
  MyMatrix AsMatrix( const std::string& ErrorId,int * pxlret=0) const;


  //! Converts to a XlfRef.
  XlfRef AsRef(int * pxlret = 0) const;

  //! Gets the internal LPXLOPER12.
  LPXLOPER12 GetLPXLOPER() const;

  //! Set the underlying XLOPER * to lpxloper.
  XlfOper12& Set(LPXLOPER12 lpxloper);
  //! Set to a double.
  XlfOper12& Set(double value);
  //! Set to a short.
  XlfOper12& Set(short value);
  //! Set to a boolean.
  XlfOper12& Set(bool value);
  //! Set to a zero-terminated character string.
  XlfOper12& Set(const char *value);
  //! Set to a wstring.
  XlfOper12& Set(const std::wstring &value);
  //! Set to a cell matrix.
  XlfOper12& Set(const CellMatrix& cells);
  //! Set to a  matrix.
  XlfOper12& Set(const MyMatrix& matrix);
  //! Set to an array.
  XlfOper12& Set(const MyArray& values);
  //! Set to a range.
  XlfOper12& Set(const XlfRef& range);
  //! Set to a short or error, bool for disambiguation.
  XlfOper12& Set(short value, bool Error);
  //! Set to an error value.
  XlfOper12& SetError(WORD error);
  //! Cast to XLOPER12 *.
  operator LPXLOPER12();
  //! Set to an array.
  /*!
  \param r number of rows in the array
  \param c number of columns in the array
  \param it iterator pointing to the begining of a container
    of size r x c (at least) that contain the data.
  \warning Data are to be stored row-wise.
  */
  template<class FwdIt>
  XlfOper12& Set(WORD r, BYTE c, FwdIt it)
  {
    lpxloper_->xltype = xltypeMulti;
    lpxloper_->val.array.rows = r;
    lpxloper_->val.array.columns = c;
    lpxloper_->val.array.lparray = (LPXLOPER12)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER12));
    for (size_t i = 0; i < size_t(r*c); ++i, ++it)
      lpxloper_->val.array.lparray[i] = *(LPXLOPER12)XlfOper12(*it);
    return *this;
  }

    DWORD xltype() const;

private:
  //! Internal LPXLOPER12.
  LPXLOPER12 lpxloper_;

  //! Coerces method is called by conversion operators if needed (never by the user).
  int Coerce(short type, XlfOper12& res) const;

  //! Reserves memory in XLL buffer (garbage collected).
  int Allocate();

  //! Anticipates deallocation if possible.
  void Deallocate();

  //! Throws an exception when critical errors occur.
  int ThrowOnError(int) const;

  //! Throws an exception when critical errors occur but passes on an identifier to help track it down.
  int ThrowOnError(int, const std::string& identifier) const;

  //! Internally used to flag XLOPER returned by Excel.
  static int xlbitFreeAuxMem;

  //! Attempts conversion to double and returns Excel error code.
  int ConvertToDoubleVector(std::vector<double>&, DoubleVectorConvPolicy policy = UniDimensional) const;
  //! Attempts conversion to double and returns Excel error code.
  int ConvertToDouble(double&) const throw();
  //! Attempts conversion to short and returns Excel error code.
  int ConvertToShort(short&) const throw();
  //! Attempts conversion to bool and returns Excel error code.
  int ConvertToBool(bool&) const throw();
  //! Attempts conversion to int and returns Excel error code.
  int ConvertToInt(int&) const throw();
  //! Attempts conversion to string and returns Excel error code.
  int ConvertToString(char *&) const throw();
  //! Attempts conversion to wstring and returns Excel error code.
  int ConvertToWstring(std::wstring &) const throw();
  //! Attempts conversion to CellMatrix and returns Excel error code.
  int ConvertToCellMatrix( CellMatrix& output) const;
  //! Attempts conversion to Matrix and returns Excel error code.
  int ConvertToMatrix( MyMatrix& output) const;

  //! Attempts conversion to XlRef and returns Excel error code.
  int ConvertToRef(XlfRef&) const throw();
  //! Attempts conversion to XlRef and returns Excel error code.
  int XlfOper12::ConvertToErr(WORD& e) const throw();


  friend class XlfExcel;
};

#ifdef NDEBUG
#include <xlw/XlfOper12.inl>
#endif

#endif
