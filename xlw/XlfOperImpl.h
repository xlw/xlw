
/*
 Copyright (C) 2007 Eric Ehlers
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

#ifndef INC_XlfOperImpl_H
#define INC_XlfOperImpl_H

/*!
\file XlfOperImpl.h
\brief Declares class XlfOperImpl.
*/

// $Id: XlfOper.h 340 2007-10-14 15:40:31Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <xlw/XlfExcel.h>
#include <xlw/MyContainers.h>
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

    static const XlfOperImpl &instance() { return *instance_; }
    XlfOperImpl() { instance_ = this; }

//#ifndef PORT_NO_MEMBER_TEMPLATE
//    //! Container ctor.
//    template <class FwdIt>
//    virtual void init(const XlfOper &xlfOper, WORD rows, BYTE cols, FwdIt start)
//#ifdef PORT_PARTIAL_MEMBER_TEMPLATE
//    {
//        Allocate(xlfOper);
//        Set (xlfOper, rows, cols, start);
//    }
//#else
//  ;
//#endif
//#endif

    //! Dtor
    virtual void destroy(const XlfOper& xlfOper) const = 0;
    //! Free auxiliary memory associated with the XLOPER
    virtual void FreeAuxiliaryMemory(const XlfOper& xlfOper) const = 0;
    //! Assignment operator
    virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper& rhs) const = 0;

    //! Is the data missing ?
    virtual bool IsMissing(const XlfOper &xlfOper) const = 0;
    //! Is the data an error ?
    virtual bool IsError(const XlfOper &xlfOper) const = 0;

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

    //! Gets the internal LPXLFOPER.
    virtual LPXLFOPER GetLPXLFOPER(const XlfOper &xlfOper) const = 0;

    //! Set the underlying XLOPER * to lpxloper
    virtual XlfOper& Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const = 0;
    //! Set to a double
    virtual XlfOper& Set(XlfOper &xlfOper, double value) const = 0;
    //! Set to a short
    virtual XlfOper& Set(XlfOper &xlfOper, short value) const = 0;
    //! Set to a boolean
    virtual XlfOper& Set(XlfOper &xlfOper, bool value) const = 0;
    //! Set to a zero-terminated character string
    virtual XlfOper& Set(XlfOper &xlfOper, const char *value) const = 0;
    //! Set to a wstring
    virtual XlfOper& Set(XlfOper &xlfOper, const std::wstring &value) const = 0;
    //! Set to a cell matrix
    virtual XlfOper& Set(XlfOper &xlfOper, const CellMatrix& cells) const = 0;
    //! Set to a range
    virtual XlfOper& Set(XlfOper &xlfOper, const XlfRef& range) const = 0;
    //! Set to a short or error, bool for disambiguation
    virtual XlfOper& Set(XlfOper &xlfOper, short value, bool Error) const = 0;
    //! Set to an error value
    virtual XlfOper& SetError(XlfOper &xlfOper, WORD error) const = 0;
    //! Cast to XLOPER *
    virtual LPXLOPER operator_LPXLOPER(const XlfOper &xlfOper) const = 0;
    //! Cast to XLOPER12 *
    virtual LPXLOPER12 operator_LPXLOPER12(const XlfOper &xlfOper) const = 0;
    //! Cast to LPXLFOPER
    virtual LPXLFOPER operator_LPXLFOPER(const XlfOper &xlfOper) const = 0;

//#ifndef PORT_NO_MEMBER_TEMPLATE
//  //! Set to an array
//  /*!
//  \param r number of rows in the array
//  \param c number of columns in the array
//  \param it iterator pointing to the begining of a container
//    of size r x c (at least) that contain the data.
//  \warning Data are to be stored row-wise.
//  */
//  template<class FwdIt>
//  XlfOper& Set(WORD r, BYTE c, FwdIt it)
//#ifdef PORT_PARTIAL_MEMBER_TEMPLATE
//  {
//    lpxloper_->xltype = xltypeMulti;
//    lpxloper_->val.array.rows = r;
//    lpxloper_->val.array.columns = c;
//    lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
//    for (size_t i = 0; i < size_t(r*c); ++i, ++it)
//      lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
//    return *this;
//  }
//#else
//  ;
//#endif
//#endif

    //! Coerce method is called by conversion operators if needed (never by the user).
    virtual int Coerce(const XlfOper &xlfOper, short type, XlfOper& res) const = 0;

    //! Reserves memory in XLL buffer (garbage collected).
    virtual int Allocate(XlfOper &xlfOper) const = 0;

    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const = 0;
    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDouble(const XlfOper &xlfOper, double& value) const throw() = 0;
    //! Attempts conversion to short and returns Excel4 error code.
    virtual int ConvertToShort(const XlfOper &xlfOper, short& value) const throw() = 0;
    //! Attempts conversion to bool and returns Excel4 error code.
    virtual int ConvertToBool(const XlfOper &xlfOper, bool& value) const throw() = 0;
    //! Attempts conversion to int and returns Excel4 error code.
    //virtual int ConvertToInt(const XlfOper &xlfOper, int& value) const throw() = 0;
    //! Attempts conversion to string and returns Excel4 error code.
    virtual int ConvertToString(const XlfOper &xlfOper, char *& value) const throw() = 0;
    //! Attempts conversion to CellMatrix and returns Excel4 error code
    virtual int ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const = 0;
    //! Attempts conversion to Matrix and returns Excel4 error code
    virtual int ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& output) const = 0;

    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToRef(const XlfOper &xlfOper, XlfRef& value) const throw() = 0;
    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw() = 0;

private:

    static XlfOperImpl *instance_;

};

//#ifdef PORT_NO_MEMBER_TEMPLATE
///*!
//\brief Set an array to an XlfOper.
//Because not all compilers support member templates this function
//is provided in order to replace the template method Set(WORD,BYTE,FwdIt).
//*/
//template <class FwdIt>
//XlfOper& XlfOperSet(XlfOper& oper, WORD rows, BYTE cols, FwdIt it)
//{
//  LPXLOPER lpxloper=oper;
//  lpxloper->xltype = xltypeMulti;
//  lpxloper->val.array.rows = rows;
//  lpxloper->val.array.columns = cols;
//  lpxloper->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(rows*cols*sizeof(XLOPER));
//  for (size_t i = 0; i < rows*cols; ++i, ++it)
//    lpxloper->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
//  return oper;
//}
//#else
//#ifndef PORT_PARTIAL_MEMBER_TEMPLATE
///*!
//\param r number of rows in the array
//\param c number of columns in the array
//\param it iterator pointing to the begining of a container
//of size r x c (at least) that contain the data.
//\warning Data are to be stored row-wise.
//*/
//template<class FwdIt>
//XlfOper& XlfOper::Set<FwdIt>(WORD r, BYTE c, FwdIt it);
//{
//  lpxloper_->xltype = xltypeMulti;
//  lpxloper_->val.array.rows = r;
//  lpxloper_->val.array.columns = c;
//  lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
//  for (size_t i = 0; i < r*c; ++i, ++it)
//    lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
//  return *this;
//}
//#endif
//#endif

#endif
