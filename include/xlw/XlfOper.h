
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

#ifndef INC_XlfOper_H
#define INC_XlfOper_H

/*!
\file XlfOper.h
\brief Declares class XlfOper.
*/

// $Id$

#include <xlw/XlfOperImpl.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Wrapper around a pointer to the XLOPER Excel data structure.
/*!
This class eases the work of marshalling and unmarshalling data to
the Excel XLOPER format (including memory).

XlfOper holds a pointer to a XLOPER.

\warning It is important \e not to add any data members to this class
because the library heavily relies on the fact that LPXLOPER and
XlfOper have the same size. It allows the library to interpret any
LPXLOPER sent by Excel as an XlfOper.
*/
class EXCEL32_API XlfOper
{
    friend class XlfOperImpl;
    friend class XlfOperImpl4;
    friend class XlfOperImpl12;
    friend class XlfExcel;

public:

    //! Default ctor.
    XlfOper();
    //! Copy ctor.
    XlfOper(const XlfOper& oper);
    //! XLOPER * ctor.
    XlfOper(LPXLFOPER lpxloper) : lpxloper4_(reinterpret_cast<LPXLOPER>(lpxloper)) {}
    //! double ctor.
    XlfOper(double value);
    //! short ctor.
    XlfOper(short value);
    //! short or error ctor.
    XlfOper(short value, bool Error);
    //! boolean ctor.
    XlfOper(bool value);
    //! 0 terminated character string ctor.
    XlfOper(const char *value);
    //!  string ctor.
    XlfOper(const std::string& value);
    //!  wstring ctor.
    XlfOper(const std::wstring& value);
    //! CellMatrix ctor.
    XlfOper(const CellMatrix& value);
    //! MyMatrix ctor.
    XlfOper(const MyMatrix& value);
    //! MyArray ctor.
    XlfOper(const MyArray& value);
    //! XlfRef ctor.
    XlfOper(const XlfRef& range);
    //! Container ctor.
    template <class FwdIt>
    XlfOper(RW rows, COL cols, FwdIt start)
    {
        Allocate();
        Set(rows, cols, start);
    }

    //! Constructs an Excel error.
    static XlfOper Error(WORD word);
    //! Dtor
    ~XlfOper() { XlfOperImpl::instance().destroy(*this); }
    //! Free auxiliary memory associated with the XLOPER
    void FreeAuxiliaryMemory() const  { return XlfOperImpl::instance().FreeAuxiliaryMemory(*this); }
    //! Assignment operator
    XlfOper& operator=(const XlfOper& xloper)  { return XlfOperImpl::instance().assignment_operator(*this, xloper); }

    //! Is the data missing ?
    bool IsMissing() const { return XlfOperImpl::instance().IsMissing(*this); }
    //! Is the data an error ?
    bool IsError() const { return XlfOperImpl::instance().IsError(*this); }
    //! Is the data a reference ?
    bool IsRef() const { return XlfOperImpl::instance().IsRef(*this); }
    //! Is the data a sheet reference ?
    bool IsSRef() const { return XlfOperImpl::instance().IsSRef(*this); }
    //! Is the data an array ?
    bool IsMulti() const { return XlfOperImpl::instance().IsMulti(*this); }
    //! Is the data a number ?
    bool IsNumber() const { return XlfOperImpl::instance().IsNumber(*this); }
    //! Is the data a string ?
    bool IsString() const { return XlfOperImpl::instance().IsString(*this); }
    //! Is the data a null value ?
    bool IsNil() const { return XlfOperImpl::instance().IsNil(*this); }
    //! Is the data a boolean ?
    bool IsBool() const { return XlfOperImpl::instance().IsBool(*this); }
    //! Is the data an integer ?
    bool IsInt() const { return XlfOperImpl::instance().IsInt(*this); }

    //! Converts to a double.
    double AsDouble(int *pxlret = 0) const;
    //! Converts to a double with error identifer.
    double AsDouble(const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a std::vector<double>.
    std::vector<double> AsDoubleVector(XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;
    std::vector<double> AsDoubleVector(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;

    //! Converts to an array.
    MyArray AsArray(XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;
    MyArray AsArray(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;

    //! Converts to a short.
    short AsShort(int *pxlret = 0) const;
    //! Converts to a short with error identifer.
    short AsShort(const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a bool.
    bool AsBool(int *pxlret = 0) const;
    //! Converts to a bool with error identifer.
    bool AsBool(const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to an int.
    int AsInt(int *pxlret = 0) const;
    //! Converts to an int with error identifer.
    int AsInt(const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a char *.
    char *AsString(int *pxlret = 0) const;
    //! Converts to a char * with error identifer.
    char *AsString(const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a wstring.
    std::wstring AsWstring(int *pxlret = 0) const;

    //! Converts to a cell Matrix.
    CellMatrix AsCellMatrix(int *pxlret=0) const;
    //! Converts to a cell Matrix with error identifer.
    CellMatrix AsCellMatrix(const std::string& ErrorId, int *pxlret=0) const;

    //! Converts to a matrix.
    MyMatrix AsMatrix(int *pxlret=0) const;
    //! Converts to a matrix with error identifer.
    MyMatrix AsMatrix(const std::string& ErrorId, int *pxlret=0) const;

    //! Converts to a XlfRef.
    XlfRef AsRef(int *pxlret = 0) const;

    //! Gets the internal LPXLFOPER.
    LPXLFOPER GetLPXLFOPER() const { return XlfOperImpl::instance().GetLPXLFOPER(*this); }

    //! Set the underlying XLOPER * to lpxloper.
    XlfOper& Set(LPXLFOPER lpxlfoper) { return XlfOperImpl::instance().Set(*this, lpxlfoper); }
    //! Set to a double.
    XlfOper& Set(double value) { return XlfOperImpl::instance().Set(*this, value); }
    //! Set to a short.
    XlfOper& Set(short value) { return XlfOperImpl::instance().Set(*this, value); }
    //! Set to a boolean.
    XlfOper& Set(bool value) { return XlfOperImpl::instance().Set(*this, value); }
    //! Set to a zero-terminated character string.
    XlfOper& Set(const char *value) { return XlfOperImpl::instance().Set(*this, value); }
    //! Set to a wstring.
    XlfOper& Set(const std::wstring &value) { return XlfOperImpl::instance().Set(*this, value); }
    //! Set to a cell matrix.
    XlfOper& Set(const CellMatrix& cells) { return XlfOperImpl::instance().Set(*this, cells); }
    //! Set to a  matrix.
    XlfOper& Set(const MyMatrix& matrix);
    //! Set to an array.
    XlfOper& Set(const MyArray& values);
    //! Set to a range.
    XlfOper& Set(const XlfRef& range) { return XlfOperImpl::instance().Set(*this, range); }
    //! Set to a short or error, bool for disambiguation.
    XlfOper& Set(short value, bool Error) { return XlfOperImpl::instance().Set(*this, value, Error); }
    //! Set to an array.
    /*!
    \param rows number of rows in the array
    \param cols number of columns in the array
    \param it iterator pointing to the begining of a container
     of size r x c (at least) that contain the data.
    \warning Data are to be stored row-wise.
    */
    template<class FwdIt>
    XlfOper& Set(RW rows, COL cols, FwdIt it)
    {
        return XlfOperImpl::instance().Set(*this, rows, cols, it);
    }

    //! Set to an error value.
    XlfOper& SetError(WORD error) { return XlfOperImpl::instance().SetError(*this, error); }

    //! Cast to XLOPER *.
    operator LPXLOPER() { return XlfOperImpl::instance().operator_LPXLOPER(*this); }
    //! Cast to XLOPER12 *.
    operator LPXLOPER12() { return XlfOperImpl::instance().operator_LPXLOPER12(*this); }
    //! Cast to LPXLFOPER.
    operator LPXLFOPER() { return XlfOperImpl::instance().operator_LPXLFOPER(*this); }

    DWORD xltype() const { return XlfOperImpl::instance().xltype(*this); }
    std::string xltypeName () const;

private:

    //! Internal LPXLOPER.
    union {
        LPXLOPER lpxloper4_;
        LPXLOPER12 lpxloper12_;
    };

    //! Coerce method is called by conversion operators if needed (never by the user).
    int Coerce(short type, XlfOper& res) const { return XlfOperImpl::instance().Coerce(*this, type, res); }

    //! Reserves memory in XLL buffer (garbage collected).
    int Allocate() { return XlfOperImpl::instance().Allocate(*this); }

    //! Throws an exception when critical errors occur.
    int ThrowOnError(int value) const;

    //! Throws an exception when critical errors occur but passes on an identifier to help track it down.
    int ThrowOnError(int value, const std::string& identifier) const;

    //! Internally used to flag XLOPER returned by Excel.
    static int xlbitFreeAuxMem;

    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDoubleVector(std::vector<double>& value, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional) const
         { return XlfOperImpl::instance().ConvertToDoubleVector(*this, value, policy); }
    //! Attempts conversion to double and returns Excel error code.
    int ConvertToDouble(double& value) const throw() {
        return XlfOperImpl::instance().ConvertToDouble(*this, value); }
    //! Attempts conversion to short and returns Excel error code.
    int ConvertToShort(short& value) const throw() {
        return XlfOperImpl::instance().ConvertToShort(*this, value); }
    //! Attempts conversion to bool and returns Excel error code.
    int ConvertToBool(bool& value) const throw() {
        return XlfOperImpl::instance().ConvertToBool(*this, value); }
    //! Attempts conversion to int and returns Excel error code.
    //int ConvertToInt(int& value) const throw() {
    //    return XlfOperImpl::instance().ConvertToInt(*this, value); }
    //! Attempts conversion to string and returns Excel error code.
    int ConvertToString(char *& value) const throw() {
        return XlfOperImpl::instance().ConvertToString(*this, value); }
    //! Attempts conversion to wstring and returns Excel error code.
	int ConvertToWstring(std::wstring &value) const throw() {
        return XlfOperImpl::instance().ConvertToWstring(*this, value); }
    //! Attempts conversion to CellMatrix and returns Excel error code.
    int ConvertToCellMatrix(CellMatrix& output) const {
        return XlfOperImpl::instance().ConvertToCellMatrix(*this, output); }
    //! Attempts conversion to Matrix and returns Excel error code.
    int ConvertToMatrix(MyMatrix& output) const {
        return XlfOperImpl::instance().ConvertToMatrix(*this, output); }

    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToRef(XlfRef& ref) const throw() {
        return XlfOperImpl::instance().ConvertToRef(*this, ref); }
    //! Attempts conversion to XlRef and returns Excel error code.
    int ConvertToErr(WORD& e) const throw() {
        return XlfOperImpl::instance().ConvertToErr(*this, e); }

};

#ifdef NDEBUG
#include <xlw/XlfOper.inl>
#endif

#endif
