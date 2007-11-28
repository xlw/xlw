
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

#ifndef INC_XlfOperImpl12_H
#define INC_XlfOperImpl12_H

/*!
\file XlfOperImpl12.h
\brief Declares class XlfOperImpl12.
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
class EXCEL32_API XlfOperImpl12 : public XlfOperImpl
{
private:

    //! Dtor
    virtual void destroy(const XlfOper &xlfOper) const;
    //! Free auxiliary memory associated with the XLOPER
    virtual void FreeAuxiliaryMemory(const XlfOper &xlfOper) const;
    //! Assignment operator
    virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const;

    //! Is the data missing ?
    virtual bool IsMissing(const XlfOper &xlfOper) const;
    //! Is the data an error ?
    virtual bool IsError(const XlfOper &xlfOper) const;

    //! Gets the internal LPXLFOPER.
    virtual LPXLFOPER GetLPXLFOPER(const XlfOper &xlfOper) const;

    //! Set the underlying XLOPER * to lpxloper
    virtual XlfOper& Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const;
    //! Set to a double
    virtual XlfOper& Set(XlfOper &xlfOper, double value) const;
    //! Set to a short
    virtual XlfOper& Set(XlfOper &xlfOper, short value) const;
    //! Set to a boolean
    virtual XlfOper& Set(XlfOper &xlfOper, bool value) const;
    //! Set to a zero-terminated character string
    virtual XlfOper& Set(XlfOper &xlfOper, const char *value) const;
    //! Set to a wstring
    virtual XlfOper& Set(XlfOper &xlfOper, const std::wstring &value) const;
    //! Set to a cell matrix
    virtual XlfOper& Set(XlfOper &xlfOper, const CellMatrix& cells) const;
    //! Set to a range
    virtual XlfOper& Set(XlfOper &xlfOper, const XlfRef& range) const;
    //! Set to a short or error, bool for disambiguation
    virtual XlfOper& Set(XlfOper &xlfOper, short value, bool Error) const;
    //! Set to an error value
    virtual XlfOper& SetError(XlfOper &xlfOper, WORD error) const;
    //! Cast to XLOPER *
    virtual LPXLOPER operator_LPXLOPER(const XlfOper &xlfOper) const;
    //! Cast to XLOPER12 *
    virtual LPXLOPER12 operator_LPXLOPER12(const XlfOper &xlfOper) const;
    //! Cast to LPXLFOPER
    virtual LPXLFOPER operator_LPXLFOPER(const XlfOper &xlfOper) const;

    //! Coerce method is called by conversion operators if needed (never by the user).
    virtual int Coerce(const XlfOper &xlfOper, short type, XlfOper& res) const;

    //! Reserves memory in XLL buffer (garbage collected).
    virtual int Allocate(XlfOper &xlfOper) const;

    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const;
    //! Attempts conversion to double and returns Excel4 error code.
    virtual int ConvertToDouble(const XlfOper &xlfOper, double& value) const throw();
    //! Attempts conversion to short and returns Excel4 error code.
    virtual int ConvertToShort(const XlfOper &xlfOper, short& value) const throw();
    //! Attempts conversion to bool and returns Excel4 error code.
    virtual int ConvertToBool(const XlfOper &xlfOper, bool& value) const throw();
    //! Attempts conversion to int and returns Excel4 error code.
    //virtual int ConvertToInt(const XlfOper &xlfOper, int& value) const throw();
    //! Attempts conversion to string and returns Excel4 error code.
    virtual int ConvertToString(const XlfOper &xlfOper, char *& value) const throw();
    //! Attempts conversion to CellMatrix and returns Excel4 error code
    virtual int ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const;
    //! Attempts conversion to Matrix and returns Excel4 error code
    virtual int ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& output) const;

    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToRef(const XlfOper &xlfOper, XlfRef& value) const throw();
    //! Attempts conversion to XlRef and returns Excel4 error code.
    virtual int ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw();
};

#endif
