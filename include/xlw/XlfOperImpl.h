
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

#ifndef INC_XlfOperImpl_H
#define INC_XlfOperImpl_H

/*!
\file XlfOperImpl.h
\brief Class XlfOperImpl - Abstract implementation of class XlfOper
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

namespace xlw {

    class XlfOper;
    class XlfOperImpl4;
    class XlfOperImpl12;
    class XlfRef;
    class CellMatrix;

    //! Abstract implementation of class XlfOper.
    /*!
    This class defines the implementation of class XlfOper.  This class is an
    abstract base class, and a singleton.  At startup, the application must
    instantiate the singleton via a concrete base class specific to the version of
    Excel that is running.  XlfOper forwards all its calls to XlfOperImpl for
    execution by the appropriate concrete base class.

    The application should never access XlfOperImpl directly.

    The interface for this class is otherwise the same as that for class XlfOper.
    */
    class EXCEL32_API XlfOperImpl
    {
        friend class XlfOper;
        friend class XlfOperImpl4;
        friend class XlfOperImpl12;

    public:

        enum DoubleVectorConvPolicy
        {
            UniDimensional,
            RowMajor,
            ColumnMajor
        };

    private:

        static const XlfOperImpl &instance() { return *instance_; }
        XlfOperImpl() { instance_ = this; }

        virtual void destroy(const XlfOper& xlfOper) const = 0;
        virtual void FreeAuxiliaryMemory(const XlfOper& xlfOper) const = 0;
        virtual XlfOper& assignment_operator(XlfOper &xlfOper, const XlfOper& rhs) const = 0;

        virtual bool IsMissing(const XlfOper &xlfOper) const = 0;
        virtual bool IsError(const XlfOper &xlfOper) const = 0;
        virtual bool IsRef(const XlfOper &xlfOper) const = 0;
        virtual bool IsSRef(const XlfOper &xlfOper) const = 0;
        virtual bool IsMulti(const XlfOper &xlfOper) const = 0;
        virtual bool IsNumber(const XlfOper &xlfOper) const = 0;
        virtual bool IsString(const XlfOper &xlfOper) const = 0;
        virtual bool IsNil(const XlfOper &xlfOper) const = 0;
        virtual bool IsBool(const XlfOper &xlfOper) const = 0;
        virtual bool IsInt(const XlfOper &xlfOper) const = 0;

        virtual LPXLFOPER GetLPXLFOPER(const XlfOper &xlfOper) const = 0;

        virtual XlfOper& Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, double value) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, short value) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, bool value) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, const char *value) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, const std::wstring &value) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, const CellMatrix& cells) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, const XlfRef& range) const = 0;
        virtual XlfOper& Set(XlfOper &xlfOper, short value, bool Error) const = 0;
        virtual XlfOper& SetError(XlfOper &xlfOper, WORD error) const = 0;
        virtual LPXLOPER operator_LPXLOPER(const XlfOper &xlfOper) const = 0;
        virtual LPXLOPER12 operator_LPXLOPER12(const XlfOper &xlfOper) const = 0;
        virtual LPXLFOPER operator_LPXLFOPER(const XlfOper &xlfOper) const = 0;

        virtual int Coerce(const XlfOper &xlfOper, short type, XlfOper& res) const = 0;

        virtual int Allocate(XlfOper &xlfOper) const = 0;

        virtual int ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& value, DoubleVectorConvPolicy policy = UniDimensional) const = 0;
        virtual int ConvertToDouble(const XlfOper &xlfOper, double& value) const throw() = 0;
        virtual int ConvertToShort(const XlfOper &xlfOper, short& value) const throw() = 0;
        virtual int ConvertToBool(const XlfOper &xlfOper, bool& value) const throw() = 0;
        virtual int ConvertToString(const XlfOper &xlfOper, char *& value) const throw() = 0;
	    virtual int ConvertToWstring(const XlfOper &xlfOper, std::wstring &value) const throw() = 0;
        virtual int ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const = 0;
        virtual int ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& output) const = 0;

        virtual int ConvertToRef(const XlfOper &xlfOper, XlfRef& value) const throw() = 0;
        virtual int ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw() = 0;

        virtual DWORD xltype(const XlfOper &xlfOper) const = 0;

        // FIXME this template doesn't compile under MinGW.
        // For the moment it is not used by the MinGW examples.
    #if defined(_MSC_VER)
        template <class FwdIt>
        XlfOper& Set(XlfOper& xlfOper, RW rows, COL cols, FwdIt it) const
        {
		    if (XlfExcel::Instance().excel12()) {

			    xlfOper.lpxloper12_->xltype = xltypeMulti;
			    xlfOper.lpxloper12_->val.array.rows = rows;
			    xlfOper.lpxloper12_->val.array.columns = cols;
			    xlfOper.lpxloper12_->val.array.lparray =
				    (LPXLOPER12)XlfExcel::Instance().GetMemory(rows * cols * sizeof(XLOPER12));
			    for (int i = 0; i < rows * cols; ++i, ++it)
				    xlfOper.lpxloper12_->val.array.lparray[i] = *(LPXLOPER12)XlfOper(*it);
			    return xlfOper;

		    } else {

			    // Excel 4 stores rows as type WORD and columns as type BYTE.
			    // Excel 12 stores rows as type RW and columns as type COL.
			    // Since this function supports both platforms, the arguments are declared with
			    // the Excel 12 types and bounds checking for Excel 4 is done at run time:

			    if (rows > USHRT_MAX) {
				    std::ostringstream err;
				    err << "Matrix row count " << rows << " exceeds Excel4 max " << USHRT_MAX;
				    throw(err.str());
			    }

			    if (cols > USHRT_MAX) {
				    std::ostringstream err;
				    err << "Matrix col count " << cols << " exceeds Excel4 max " << USHRT_MAX;
				    throw(err.str());
			    }

			    xlfOper.lpxloper4_->xltype = xltypeMulti;
			    xlfOper.lpxloper4_->val.array.rows = rows;
			    xlfOper.lpxloper4_->val.array.columns = cols;
			    xlfOper.lpxloper4_->val.array.lparray =
				    (LPXLOPER)XlfExcel::Instance().GetMemory(rows * cols * sizeof(XLOPER));
			    for (int i = 0; i < rows*cols; ++i, ++it)
				    xlfOper.lpxloper4_->val.array.lparray[i] = *(LPXLOPER)XlfOper(*it);
			    return xlfOper;

		    }
        }
    #endif

        static XlfOperImpl *instance_;

    };

}

#endif

