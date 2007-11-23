
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

#ifndef INC_XlfOperImpl_H
#define INC_XlfOperImpl_H

/*!
\file XlfOperImpl.h
\brief Declares class XlfOperImpl.
*/

// $Id: XlfOper.h 340 2007-10-14 15:40:31Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <xlw/XlfOperUnion.h>
#include <xlw/XlfExcel.h>
#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include <xlw/XlfRef.h>
#include <vector>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

class XlfOper;
class XlfRef;
class CellMatrix;

typedef void* LPXLFOPER;

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
class EXCEL32_API XlfOperImpl
{
public:

    static const XlfOperImpl &instance();
    XlfOperImpl() { instance_ = this; }

    //! Default ctor.
    void Init(XlfOperUnion &xlfOperUnion) const;
    //! double ctor.
    void Init(XlfOperUnion &xlfOperUnion, double value) const;
    //! short ctor.
    void Init(XlfOperUnion &xlfOperUnion, short value) const;
    //! short or error ctor.
    void Init(XlfOperUnion &xlfOperUnion, short value, bool Error) const;
    //! boolean ctor.
    void Init(XlfOperUnion &xlfOperUnion, bool value) const;
    //! 0 terminated character string ctor.
    void Init(XlfOperUnion &xlfOperUnion, const char *value) const;
    //!  string ctor.
    void Init(XlfOperUnion &xlfOperUnion, const std::string& value) const;
    //!  wstring ctor.
    void Init(XlfOperUnion &xlfOperUnion, const std::wstring& value) const;
    //! CellMatrix ctor
    void Init(XlfOperUnion &xlfOperUnion, const CellMatrix& value) const;
    //! MyMatrix ctor
    void Init(XlfOperUnion &xlfOperUnion, const MyMatrix& value) const;
    //! MyArray ctor
    void Init(XlfOperUnion &xlfOperUnion, const MyArray& value) const;
    //! XlfRef ctor.
    void Init(XlfOperUnion &xlfOperUnion, const XlfRef& range) const;

    //! Constructs an Excel error.
    static XlfOper Error(WORD word);
    //! Dtor
    virtual void destroy(const XlfOperUnion &xlfOperUnion) const = 0;
    //! Free auxiliary memory associated with the XLOPER
    virtual void FreeAuxiliaryMemory(const XlfOperUnion &xlfOperUnion) const = 0;
    //! Assignment operator
    virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper& rhs) const = 0;

    //! Is the data missing ?
    virtual bool IsMissing(const XlfOperUnion &xlfOperUnion) const = 0;
    //! Is the data an error ?
    virtual bool IsError(const XlfOperUnion &xlfOperUnion) const = 0;

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

    //! Converts to a double.
    double AsDouble(const XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;
    //! Converts to a double with error identifer.
    double AsDouble(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a std::vector<double>.
    std::vector<double> AsDoubleVector(const XlfOperUnion &xlfOperUnion,
        XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;
    std::vector<double> AsDoubleVector(const XlfOperUnion &xlfOperUnion,
        const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;
 
    //! Converts to an array.
    MyArray AsArray(const XlfOperUnion &xlfOperUnion,
        XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;
    MyArray AsArray(const XlfOperUnion &xlfOperUnion,
        const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional, int *pxlret = 0) const;

    //! Converts to a short.
    short AsShort(const XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;
    //! Converts to a short with error identifer.
    short AsShort(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a bool.
    bool AsBool(const XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;
    //! Converts to a bool with error identifer.
    bool AsBool(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to an int.
    int AsInt(XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;
    //! Converts to an int with error identifer.
    int AsInt(XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret = 0) const;
    //! Converts to a char *.
    char *AsString(const XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;
    //! Converts to a char * with error identifer.
    char *AsString(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret = 0) const;

    //! Converts to a cell Matrix
    CellMatrix AsCellMatrix(const XlfOperUnion &xlfOperUnion, int *pxlret=0) const;
    //! Converts to a cell Matrix with error identifer.
    CellMatrix AsCellMatrix(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret=0) const;
 
    //! Converts to a matrix
    MyMatrix AsMatrix(const XlfOperUnion &xlfOperUnion, int *pxlret=0) const;
    //! Converts to a matrix with error identifer.
    MyMatrix AsMatrix(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret=0) const;

    //! Converts to a XlfRef.
    XlfRef AsRef(const XlfOperUnion &xlfOperUnion, int *pxlret = 0) const;

    //! Gets the internal LPXLFOPER.
    virtual LPXLFOPER GetLPXLFOPER(const XlfOperUnion &xlfOperUnion) const = 0;

    //! Set the underlying XLOPER * to lpxloper
    virtual void Set(XlfOperUnion &xlfOperUnion, LPXLFOPER lpxlfoper) const = 0;
    //! Set to a double
    virtual void Set(XlfOperUnion &xlfOperUnion, double value) const = 0;
    //! Set to a short
    virtual void Set(XlfOperUnion &xlfOperUnion, short value) const = 0;
    //! Set to a boolean
    virtual void Set(XlfOperUnion &xlfOperUnion, bool value) const = 0;
    //! Set to a zero-terminated character string
    virtual void Set(XlfOperUnion &xlfOperUnion, const char *value) const = 0;
    //! Set to a wstring
    virtual void Set(XlfOperUnion &xlfOperUnion, const std::wstring &value) const = 0;
    //! Set to a cell matrix
    virtual void Set(XlfOperUnion &xlfOperUnion, const CellMatrix& cells) const = 0;
    //! Set to a  matrix
    void Set(XlfOperUnion &xlfOperUnion, const MyMatrix& values);
    //! Set to an array
    void Set(XlfOperUnion &xlfOperUnion, const MyArray& values);
    //! Set to a range
    virtual void Set(XlfOperUnion &xlfOperUnion, const XlfRef& range) const = 0;
    //! Set to a short or error, bool for disambiguation
    virtual void Set(XlfOperUnion &xlfOperUnion, short value, bool Error) const = 0;
    //! Set to an error value
    virtual void SetError(XlfOperUnion &xlfOperUnion, WORD error) const = 0;
    //! Cast to XLOPER *
    virtual LPXLOPER operator_LPXLOPER(const XlfOperUnion &xlfOperUnion) const = 0;
    //! Cast to XLOPER12 *
    virtual LPXLOPER12 operator_LPXLOPER12(const XlfOperUnion &xlfOperUnion) const = 0;
    //! Cast to LPXLFOPER
    virtual LPXLFOPER operator_LPXLFOPER(const XlfOperUnion &xlfOperUnion) const = 0;

    //! Coerce method is called by conversion operators if needed (never by the user).
    //virtual int Coerce(const XlfOperUnion &xlfOperUnion, short type, XlfOperUnion &res) const = 0;

    //! Reserves memory in XLL buffer (garbage collected).
    virtual int Allocate(XlfOperUnion &xlfOperUnion) const = 0;

    //! Internally used to flag XLOPER returned by Excel.
    static int xlbitFreeAuxMem;

    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDoubleVector(const XlfOperUnion &xlfOperUnion, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const = 0;
    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDouble(const XlfOperUnion &xlfOperUnion, double& value) const throw() = 0;
    //! Attempts conversion to short and returns Excel4 error code.
    virtual int ConvertToShort(const XlfOperUnion &xlfOperUnion, short& value) const throw() = 0;
    //! Attempts conversion to bool and returns Excel4 error code.
    virtual int ConvertToBool(const XlfOperUnion &xlfOperUnion, bool& value) const throw() = 0;
    //! Attempts conversion to int and returns Excel4 error code.
    //virtual int ConvertToInt(const XlfOperUnion &xlfOperUnion, int& value) const throw() = 0;
    //! Attempts conversion to string and returns Excel4 error code.
    virtual int ConvertToString(const XlfOperUnion &xlfOperUnion, char *& value) const throw() = 0;
    //! Attempts conversion to CellMatrix and returns Excel4 error code
    virtual int ConvertToCellMatrix(const XlfOperUnion &xlfOperUnion, CellMatrix& output) const = 0;
    //! Attempts conversion to Matrix and returns Excel4 error code
    virtual int ConvertToMatrix(const XlfOperUnion &xlfOperUnion, MyMatrix& output) const = 0;

    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToRef(const XlfOperUnion &xlfOperUnion, XlfRef& value) const throw() = 0;
    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToErr(const XlfOperUnion &xlfOperUnion, WORD& e) const throw() = 0;

protected:

    static XlfOperImpl *instance_;

private:

    //! Throws an exception when critical errors occur.
    int ThrowOnError(int value) const;
    //! Throws an exception when critical errors occur but passes on an identifier to help track it down
    int ThrowOnError(int value, const std::string& identifier) const;

};

#ifdef NDEBUG
#include <xlw/XlfOperImpl.inl>
#endif

#endif
