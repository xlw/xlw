
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

#ifndef INC_XlfOperImpl4_H
#define INC_XlfOperImpl4_H

/*!
\file XlfOperImpl4.h
\brief Declares class XlfOperImpl4.
*/

// $Id: XlfOper.h 340 2007-10-14 15:40:31Z ericehlers $

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
class EXCEL32_API XlfOperImpl4 : public XlfOperImpl
{
public:

    static const XlfOperImpl4 &instance();

private:

    //! Dtor
    virtual void destroy(const XlfOperUnion &xlfOperUnion) const;
    //! Free auxiliary memory associated with the XLOPER
    virtual void FreeAuxiliaryMemory(const XlfOperUnion &xlfOperUnion) const;
    //! Assignment operator
    virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const;

    //! Is the data missing ?
    virtual bool IsMissing(const XlfOperUnion &xlfOperUnion) const;
    //! Is the data an error ?
    virtual bool IsError(const XlfOperUnion &xlfOperUnion) const;

    //! Gets the internal LPXLFOPER.
    virtual LPXLFOPER GetLPXLFOPER(const XlfOperUnion &xlfOperUnion) const;

    //! Set the underlying XLOPER * to lpxloper
    virtual void Set(XlfOperUnion &xlfOperUnion, LPXLFOPER lpxlfoper) const;
    //! Set to a double
    virtual void Set(XlfOperUnion &xlfOperUnion, double value) const;
    //! Set to a short
    virtual void Set(XlfOperUnion &xlfOperUnion, short value) const;
    //! Set to a boolean
    virtual void Set(XlfOperUnion &xlfOperUnion, bool value) const;
    //! Set to a zero-terminated character string
    virtual void Set(XlfOperUnion &xlfOperUnion, const char *value) const;
    //! Set to a wstring
    virtual void Set(XlfOperUnion &xlfOperUnion, const std::wstring &value) const;
    //! Set to a cell matrix
    virtual void Set(XlfOperUnion &xlfOperUnion, const CellMatrix& cells) const;
    //! Set to a range
    virtual void Set(XlfOperUnion &xlfOperUnion, const XlfRef& range) const;
    //! Set to a short or error, bool for disambiguation
    virtual void Set(XlfOperUnion &xlfOperUnion, short value, bool Error) const;
    //! Set to an error value
    virtual void SetError(XlfOperUnion &xlfOperUnion, WORD error) const;
    //! Cast to XLOPER *
    virtual LPXLOPER operator_LPXLOPER(const XlfOperUnion &xlfOperUnion) const;
    //! Cast to XLOPER12 *
    virtual LPXLOPER12 operator_LPXLOPER12(const XlfOperUnion &xlfOperUnion) const;
    //! Cast to LPXLFOPER
    virtual LPXLFOPER operator_LPXLFOPER(const XlfOperUnion &xlfOperUnion) const;

    //! Coerce method is called by conversion operators if needed (never by the user).
    int Coerce(const XlfOperUnion &xlfOperUnion, short type, XlfOperUnion &result) const;

    //! Reserves memory in XLL buffer (garbage collected).
    virtual int Allocate(XlfOperUnion &xlfOperUnion) const;

    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDoubleVector(const XlfOperUnion &xlfOperUnion, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const;
    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDouble(const XlfOperUnion &xlfOperUnion, double& value) const throw();
    //! Attempts conversion to short and returns Excel4 error code.
    virtual int ConvertToShort(const XlfOperUnion &xlfOperUnion, short& value) const throw();
    //! Attempts conversion to bool and returns Excel4 error code.
    virtual int ConvertToBool(const XlfOperUnion &xlfOperUnion, bool& value) const throw();
    //! Attempts conversion to int and returns Excel4 error code.
    //virtual int ConvertToInt(const XlfOperUnion &xlfOperUnion, int& value) const throw();
    //! Attempts conversion to string and returns Excel4 error code.
    virtual int ConvertToString(const XlfOperUnion &xlfOperUnion, char *& value) const throw();
    //! Attempts conversion to CellMatrix and returns Excel4 error code
    virtual int ConvertToCellMatrix(const XlfOperUnion &xlfOperUnion, CellMatrix& output) const;
    //! Attempts conversion to Matrix and returns Excel4 error code
    virtual int ConvertToMatrix(const XlfOperUnion &xlfOperUnion, MyMatrix& output) const;

    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToRef(const XlfOperUnion &xlfOperUnion, XlfRef& value) const throw();
    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToErr(const XlfOperUnion &xlfOperUnion, WORD& e) const throw();
};

#endif
