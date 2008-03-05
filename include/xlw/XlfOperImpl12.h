
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

#ifndef INC_XlfOperImpl12_H
#define INC_XlfOperImpl12_H

/*!
\file XlfOperImpl12.h
\brief Class XlfOperImpl12 - Concrete implementation of class XlfOper for Excel 12
*/

// $Id: XlfOper.h 340 2007-10-14 15:40:31Z ericehlers $

#include <xlw/XlfOperImpl.h>

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Concrete implementation of class XlfOperImpl for Excel 12.
/*!
At startup, if xlw detects that Excel version 12 is running, xlw instantiates a
singleton instance of XlfOperImpl12, which is a concrete implementation of
abstract base class XlfOperImpl.

XlfOper forwards its calls to XlfOperImpl for execution by XlfOperImpl12.  The
application should never access XlfOperImpl directly.

The interface for this class is otherwise the same as that for class XlfOper.
*/
class EXCEL32_API XlfOperImpl12 : public XlfOperImpl
{
private:

    virtual void destroy(const XlfOper &xlfOper) const;
    virtual void FreeAuxiliaryMemory(const XlfOper &xlfOper) const;
    virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const;

    virtual bool IsMissing(const XlfOper &xlfOper) const;
    virtual bool IsError(const XlfOper &xlfOper) const;
    virtual bool IsRef(const XlfOper &xlfOper) const;
    virtual bool IsSRef(const XlfOper &xlfOper) const;
    virtual bool IsMulti(const XlfOper &xlfOper) const;
    virtual bool IsNumber(const XlfOper &xlfOper) const;
    virtual bool IsString(const XlfOper &xlfOper) const;
    virtual bool IsNil(const XlfOper &xlfOper) const;
    virtual bool IsBool(const XlfOper &xlfOper) const;
    virtual bool IsInt(const XlfOper &xlfOper) const;

    virtual LPXLFOPER GetLPXLFOPER(const XlfOper &xlfOper) const;

    virtual XlfOper& Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const;
    virtual XlfOper& Set(XlfOper &xlfOper, double value) const;
    virtual XlfOper& Set(XlfOper &xlfOper, short value) const;
    virtual XlfOper& Set(XlfOper &xlfOper, bool value) const;
    virtual XlfOper& Set(XlfOper &xlfOper, const char *value) const;
    virtual XlfOper& Set(XlfOper &xlfOper, const std::wstring &value) const;
    virtual XlfOper& Set(XlfOper &xlfOper, const CellMatrix& cells) const;
    virtual XlfOper& Set(XlfOper &xlfOper, const XlfRef& range) const;
    virtual XlfOper& Set(XlfOper &xlfOper, short value, bool Error) const;
    virtual XlfOper& SetError(XlfOper &xlfOper, WORD error) const;
    virtual LPXLOPER operator_LPXLOPER(const XlfOper &xlfOper) const;
    virtual LPXLOPER12 operator_LPXLOPER12(const XlfOper &xlfOper) const;
    virtual LPXLFOPER operator_LPXLFOPER(const XlfOper &xlfOper) const;

    virtual int Coerce(const XlfOper &xlfOper, short type, XlfOper& res) const;

    virtual int Allocate(XlfOper &xlfOper) const;

    virtual int ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const;
    virtual int ConvertToDouble(const XlfOper &xlfOper, double& value) const throw();
    virtual int ConvertToShort(const XlfOper &xlfOper, short& value) const throw();
    virtual int ConvertToBool(const XlfOper &xlfOper, bool& value) const throw();
    virtual int ConvertToString(const XlfOper &xlfOper, char *& value) const throw();
	virtual int ConvertToWstring(const XlfOper &xlfOper, std::wstring &value) const throw();
    virtual int ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const;
    virtual int ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& output) const;
    virtual int ConvertToRef(const XlfOper &xlfOper, XlfRef& value) const throw();
    virtual int ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw();

    virtual DWORD xltype(const XlfOper &xlfOper) const;
};

#endif

