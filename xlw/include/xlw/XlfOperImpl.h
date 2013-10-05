
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock

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
\file XlfOper.h
\brief Class XlfOper - Abstract implementation of class XlfOper
*/

// $Id$

//uncommenting the following line cause an INTERNAL COMPILER ERROR in VC7.1
//#include "xlw/MyContainers.h"
#include <xlw/xlcall32.h>
#include <xlw/XlfOperProperties.h>
#include <xlw/CellMatrix.h>
#include <xlw/XlfRef.h>
#include <vector>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    class XlfOperImpl
    {
    public:
        //! Internally used to flag XLOPER returned by Excel.
        static const int xlbitFreeAuxMem = xlbitXLFree;

        enum DoubleVectorConvPolicy
        {
            UniDimensional,
            RowMajor,
            ColumnMajor
        };

        //! Used to throw informative error messages
        static void ThrowOnError(int, const char* ErrorId = 0, const char* identifier = 0);
        static void MissingOrEmptyError(int xlType, const char* ErrorId = 0, const char* identifier = 0);
        static std::string XlTypeToString(int xlType);
    };
}

namespace xlw { namespace impl {

    template<typename LPOPER_TYPE>
    class EXCEL32_API XlfOper
    {
    private:
        //! \name Manage reference to the underlying XLOPER
        //@{
        //! Internal LPXLFOPER/LPXLOPER/LPXLOPER12.
        mutable LPOPER_TYPE lpxloper_;
        //@}

        typedef XlfOperProperties<LPOPER_TYPE> OperProps;
        typedef typename XlfOperProperties<LPOPER_TYPE>::ErrorType ErrorType;
        typedef typename XlfOperProperties<LPOPER_TYPE>::IntType IntType;
        typedef typename XlfOperProperties<LPOPER_TYPE>::MultiRowType MultiRowType;
        typedef typename XlfOperProperties<LPOPER_TYPE>::MultiColType MultiColType;
        typedef typename XlfOperProperties<LPOPER_TYPE>::XlTypeType XlTypeType;
        typedef typename XlfOperProperties<LPOPER_TYPE>::OperType OperType;
        typedef xlw::XlfOperImpl XlfOperImpl;

        // we need to be careful if we try and return back to excel memory it
        // has given us as a return value 
        // some versions object to the flag we use for memory management.
        // To avoid this being a problem we 
        // take a deep copy and free the Excel version
        // whenever we cast to a LPXLOPER pointer.
        // This means we only use additional temp memory
        // and data copy if we pass the result of one excel call
        // back into excel or return it as a result
        void prepareForPointerCast() const
        {
            XlTypeType type = OperProps::getXlType(lpxloper_);
            if (type & xlw::XlfOperImpl::xlbitFreeAuxMem)
            {
                LPOPER_TYPE result = TempMemory::GetMemory<OperType>();
                type &= ~xlw::XlfOperImpl::xlbitFreeAuxMem;
                OperProps::setXlType(lpxloper_, type);
                OperProps::copy(lpxloper_, result);
                OperProps::XlFree(lpxloper_);
                lpxloper_ = result;
            }
        }

    public:

        //! \name Array settor
        //@{
        /// Set the underlying XLOPER from a forward iterator.
        ///
        /// The iterator must point to a value that can be set
        /// using an equality operator, that is one of
        /// XlfOper LPXLFOPER, double, int, bool, char* wchar_t*
        /// std::string std::wstring
        template <class FwdIt>
        void Set(RW rows, COL cols, FwdIt start)
        {
            OperProps::setArraySize(lpxloper_, rows, cols);
            RW actualrows = OperProps::getRows(lpxloper_);
            COL actualcols = OperProps::getCols(lpxloper_);
            for(MultiRowType row(0); row < actualrows; ++row)
            {
                for(MultiRowType col(0); col < actualcols; ++col)
                {
                    XlfOper<LPOPER_TYPE> cellToSet(OperProps::getElement(lpxloper_, row, col));
                    cellToSet = *start++;
                }
                start += (cols - actualcols);
            }
        }
        //@}

        //! \name Structors and static members
        //@{
        //! Default ctor.
        XlfOper() :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setXlType(lpxloper_, xltypeMissing);
        }
        //! Copy ctor.
        XlfOper(const XlfOper<LPOPER_TYPE>& oper) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::copy(oper.lpxloper_, lpxloper_);
        }

        //! LPXLOPER/LPXLOPER12 ctor.
        XlfOper(LPOPER_TYPE lpxloper) :
            lpxloper_(lpxloper)
        {
        }
        //! double ctor.
        XlfOper(double value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setDouble(lpxloper_, value);
        }
        //! short ctor.
        XlfOper(short value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setInt(lpxloper_, value);
        }
        //! int ctor.
        XlfOper(int value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setInt(lpxloper_, value);
        }
        //! unsigned long ctor.
        XlfOper(unsigned long value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setDouble(lpxloper_, static_cast<double>(value));
        }

        //! boolean ctor.
        XlfOper(bool value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setBool(lpxloper_, value);
        }

        //! Cellmatrix ctor.
        XlfOper(const CellMatrix& cellmatrix) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            RW nbRows = (RW)cellmatrix.RowsInStructure();
            COL nbCols = (COL)cellmatrix.ColumnsInStructure();

            OperProps::setArraySize(lpxloper_, nbRows, nbCols);

            // get actual number of rows in case of truncation
            nbRows = OperProps::getRows(lpxloper_);
            nbCols = OperProps::getCols(lpxloper_);

            for (RW row(0); row < nbRows; ++row)
            {
                for (COL col(0); col < nbCols; ++col)
                {
                    LPOPER_TYPE elementOper = OperProps::getElement(lpxloper_, row, col);
                    const CellValue& cellValue(cellmatrix(row,col));
                    if (cellValue.IsANumber())
                    {
                        OperProps::setDouble(elementOper, cellValue.NumericValue());
                    }
                    else if (cellValue.IsAString())
                    {
                        OperProps::setString(elementOper, cellValue.StringValue());
                    }
                    else if (cellValue.IsAWstring())
                    {
                        OperProps::setWString(elementOper, cellValue.WstringValue());
                    }
                    else if (cellValue.IsBoolean())
                    {
                        OperProps::setBool(elementOper, cellValue.BooleanValue());
                    }
                    else if (cellValue.IsError())
                    {
                        OperProps::setError(elementOper, static_cast<short>(cellValue.ErrorValue()));
                    }
                    else
                    {
                        OperProps::setString(elementOper, "");
                    }
                }
            }
        }

        //! MyMatrix ctor.
        XlfOper(const MyMatrix& matrix) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            RW nbRows = (RW)MatrixTraits<MyMatrix>::rows(matrix);
            COL nbCols = (COL)MatrixTraits<MyMatrix>::columns(matrix);

            OperProps::setArraySize(lpxloper_, nbRows, nbCols);

            // get actual number of rows in case of truncation
            nbRows = OperProps::getRows(lpxloper_);
            nbCols = OperProps::getCols(lpxloper_);

            for (RW row(0); row < nbRows; ++row)
            {
                for (COL col(0); col < nbCols; ++col)
                {
                    LPOPER_TYPE elementOper = OperProps::getElement(lpxloper_, row, col);
                    OperProps::setDouble(elementOper, MatrixTraits<MyMatrix>::getAt(matrix, row, col));
                }
            }
        }

        //! MyArray ctor.
        XlfOper(const MyArray& values) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            RW nbRows = (RW)ArrayTraits<MyArray>::size(values);

            OperProps::setArraySize(lpxloper_, nbRows, 1);

            // get actual number of rows in case of truncation
            nbRows = OperProps::getRows(lpxloper_);

            for (RW row(0); row < nbRows; ++row)
            {
                LPOPER_TYPE elementOper = OperProps::getElement(lpxloper_, row, 0);
                OperProps::setDouble(elementOper, ArrayTraits<MyArray>::getAt(values, row));
            }
        }
        //!  string ctor.
        XlfOper(const std::string& value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setString(lpxloper_, value);
        }
        //!  string ctor.
        XlfOper(const char* value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setString(lpxloper_, value);
        }
        //!  wide string ctor.
        XlfOper(const wchar_t* value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setWString(lpxloper_, value);
        }
        //!  wstring ctor.
        XlfOper(const std::wstring& value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setWString(lpxloper_, value);
        }
        //!  XlfRef ctor.
        XlfOper(const XlfRef& value) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setRef(lpxloper_, value);
        }
        //! XlfMulti ctor.
        XlfOper(RW rows, COL cols) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            OperProps::setArraySize(lpxloper_, rows, cols);
        }

        //! Container ctor.
        template <class FwdIt>
        XlfOper(RW rows, COL cols, FwdIt start) :
            lpxloper_(TempMemory::GetMemory<OperType>())
        {
            Set(rows, cols, start);
        }
        //! Destructor
        ~XlfOper()
        {
            XlTypeType type = OperProps::getXlType(lpxloper_);

            if (type & xlw::XlfOperImpl::xlbitFreeAuxMem)
            {
                // switch back the bit as it was originally
                type &= ~xlw::XlfOperImpl::xlbitFreeAuxMem;
                OperProps::setXlType(lpxloper_, type);
                OperProps::XlFree(lpxloper_);
            }
        }

        //! Constructs an Excel error.
        static XlfOper<LPOPER_TYPE> Error(ErrorType errorCode)
        {
            XlfOper<LPOPER_TYPE> result;
            result.SetError(errorCode);
            return result;
        }
        //@}

        //! \name Operators
        //@{
        //! Cast to XLOPER *.
        operator LPOPER_TYPE()
        {
            prepareForPointerCast();
            return lpxloper_;
        }
        //! Cast to const XLOPER *.
        operator const LPOPER_TYPE() const
        {
            prepareForPointerCast();
            return lpxloper_;
        }
        //@}

        //! \name Inspectors
        //@{
        //! Is the data missing, used by Excel to flag a paramter that hasn't been supplied ?
        bool IsMissing() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeMissing) != 0;
        }
        //! Is the data an error ?
        bool IsError() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeErr) != 0;
        }
        //! Is the data a reference ?
        bool IsRef() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeRef) != 0;
        }
        //! Is the data a sheet reference ?
        bool IsSRef() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeSRef) != 0;
        }
        //! Is the data an array ?
        bool IsMulti() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeMulti) != 0;
        }
        //! Is the data a number ?
        bool IsNumber() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeNum) != 0;
        }
        //! Is the data a string ?
        bool IsString() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeStr) != 0;
        }
        //! Is the data a null value ?
        bool IsNil() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeNil) != 0;
        }

        //! Is the data a boolean ?
        bool IsBool() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeBool) != 0;
        }
        //! Is the data an integer ?
        bool IsInt() const
        {
            return (OperProps::getXlType(lpxloper_) & xltypeInt) != 0;
        }

        //! The Excel code for the underlying datatype
        XlTypeType xltype() const { return OperProps::getXlType(lpxloper_);}

        //! String representation of the Excel code for the underlying datatype
        std::string xltypeName() const
        {
            return xlw::XlfOperImpl::XlTypeToString(OperProps::getXlType(lpxloper_));
        }
        //@}

        /*! \name Array Accessors / Operators
        These functions are used to access the elements of an array in an XlfOper
        whose underlying <tt>LPXLOPER/LPXLOPER12</tt> has <tt>xltype = xltypeMulti</tt>.

        Here is an example of how this interface can be used to inspect
        a value received from Excel as an input to an addin function.
        \code
        LPXLFOPER EXCEL_EXPORT test_sum(LPXLFOPER operInput) {
            EXCEL_BEGIN;
            XlfOper xlInput(operInput);
            double sum = 0.;
            for (RW i = 0; i < xlInput.rows(); i++)
                for (COL j = 0; j < xlInput.columns(); j++)
                    sum += xlInput(i, j).AsDouble();
            return XlfOper(sum);

            EXCEL_END;
        }
        \endcode

        Here is an example of how this interface can be used to populate an array
        to be returned to Excel from an addin function.
        \code
        XlfOper ret(3, 2);
        ret(0, 0) = "abc";
        ret(0, 1) = (short)42;
        ret(1, 0) = 1.23;
        ret(1, 1) = XlfOper::Error(xlerrValue);
        ret(2, 0) = true;
        \endcode
        */
        //! Number of rows in matrix.
        MultiRowType rows() const
        {
            return OperProps::getRows(lpxloper_);
        }

        //! Number of columns in matrix.
        MultiColType columns() const
        {
            return OperProps::getCols(lpxloper_);
        }

        //! Function call operator, used here to subscript a two dimensional array.
        XlfOper<LPOPER_TYPE> operator()(MultiRowType row, MultiColType col)
        {
            return XlfOper<LPOPER_TYPE>(OperProps::getElement(lpxloper_, row, col));
        }

        //! Set the value of array element with specified subscript.
        void SetElement(MultiRowType r, MultiColType c, const XlfOper<LPOPER_TYPE> &value)
        {
            switch(OperProps::getXlType(lpxloper_) & 0xFFF)
            {
            case xltypeMulti:
                OperProps::copy(value.lpxloper_, OperProps::getElement(lpxloper_, r, c));
                break;

            case xltypeNum:
            case xltypeStr:
            case xltypeBool:
            case xltypeInt:
                OperProps::copy(value.lpxloper_, lpxloper_);
                break;

            default:
                THROW_XLW("Wrong type for element by element access ");
                break;
            }
        }
        //@}

        //! \name Conversions
        //@{
        //! Converts to a double with error identifer.
        double AsDouble(const char* ErrorId = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            switch(type)
            {
            case xltypeNum:
                return OperProps::getDouble(lpxloper_);
                break;

            case xltypeBool:
                return OperProps::getBool(lpxloper_);
                break;

            case xltypeInt:
                return OperProps::getInt(lpxloper_);
                break;

            case xltypeMissing:
            case xltypeErr:
            case xltypeNil:
                xlw::XlfOperImpl::MissingOrEmptyError(type, ErrorId, "Conversion to Double");
                throw XlfNeverGetHere();
                break;

            default:
                break;
            }
            OperType stackMem;
            int xlret = OperProps::coerce(lpxloper_, xltypeNum, &stackMem);
            if(xlret == xlretSuccess)
            {
                XlfOper<LPOPER_TYPE> result(&stackMem);
                return result.AsDouble(ErrorId);
            }
            else
            {
                xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to Double");
                throw XlfNeverGetHere();
            }
        }

        XlfRef AsRef(const char* ErrorId = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            if(type == xltypeRef)
            {
                return OperProps::getRef(lpxloper_);
            }
            else
            {
                OperType stackMem;
                int xlret = OperProps::coerce(lpxloper_, xltypeRef, &stackMem);
                if(xlret == xlretSuccess)
                {
                    XlfOper<LPOPER_TYPE> result(&stackMem);
                    return result.AsRef(ErrorId);
                }
                else
                {
                    xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to Ref");
                    throw XlfNeverGetHere();
                }
            }
        }

        //! Converts to a short with error identifer.
        short AsShort(const char* ErrorId = 0, int *pxlret = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            switch(type)
            {
            case xltypeNum:
                return static_cast<short>(OperProps::getDouble(lpxloper_));
                break;

            case xltypeBool:
                return static_cast<short>(OperProps::getBool(lpxloper_));
                break;

            case xltypeInt:
                return static_cast<short>(OperProps::getInt(lpxloper_));
                break;

            case xltypeMissing:
            case xltypeErr:
            case xltypeNil:
                xlw::XlfOperImpl::MissingOrEmptyError(type, ErrorId, "Conversion to Short");
                throw XlfNeverGetHere();
                break;

            default:
                break;
            }
            OperType stackMem;
            int xlret = OperProps::coerce(lpxloper_, xltypeNum, &stackMem);
            if(xlret == xlretSuccess)
            {
                XlfOper<LPOPER_TYPE> result(&stackMem);
                return result.AsShort(ErrorId);
            }
            else
            {
                xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to Short");
                throw XlfNeverGetHere();
            }
        }

        //! Converts to a bool with error identifer.
        bool AsBool(const char* ErrorId = 0, int *pxlret = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            switch(type)
            {
            case xltypeNum:
                return !!OperProps::getDouble(lpxloper_);
                break;

            case xltypeBool:
                return OperProps::getBool(lpxloper_);
                break;

            case xltypeInt:
                return !!OperProps::getInt(lpxloper_);
                break;

            case xltypeMissing:
            case xltypeErr:
            case xltypeNil:
                xlw::XlfOperImpl::MissingOrEmptyError(type, ErrorId, "Conversion to Bool");
                throw XlfNeverGetHere();
                break;

            default:
                break;
            }
            OperType stackMem;
            int xlret = OperProps::coerce(lpxloper_, xltypeBool, &stackMem);
            if(xlret == xlretSuccess)
            {
                XlfOper<LPOPER_TYPE> result(&stackMem);
                return result.AsBool(ErrorId);
            }
            else
            {
                xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to Bool");
                throw XlfNeverGetHere();
            }
        }

        //! Converts to an int with error identifer.
        int AsInt(const char* ErrorId = 0, int *pxlret = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            switch(type)
            {
            case xltypeNum:
                return static_cast<int>(OperProps::getDouble(lpxloper_));
                break;

            case xltypeBool:
                return static_cast<int>(OperProps::getBool(lpxloper_));
                break;

            case xltypeInt:
                return static_cast<int>(OperProps::getInt(lpxloper_));
                break;

            case xltypeMissing:
            case xltypeErr:
            case xltypeNil:
                xlw::XlfOperImpl::MissingOrEmptyError(type, ErrorId, "Conversion to int");
                throw XlfNeverGetHere();
                break;

            default:
                break;
            }
            OperType stackMem;
            int xlret = OperProps::coerce(lpxloper_, xltypeNum, &stackMem);
            if(xlret == xlretSuccess)
            {
                XlfOper<LPOPER_TYPE> result(&stackMem);
                return result.AsInt(ErrorId);
            }
            else
            {
                xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to Int");
                throw XlfNeverGetHere();
            }
        }

        //! Converts to a unsigned long with error identifer.
        unsigned long AsULong(const char* ErrorId = 0, int *pxlret = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            switch(type)
            {
            case xltypeNum:
                return static_cast<unsigned long>(OperProps::getDouble(lpxloper_));
                break;

            case xltypeBool:
                return static_cast<unsigned long>(OperProps::getBool(lpxloper_));
                break;

            case xltypeInt:
                return static_cast<unsigned long>(OperProps::getInt(lpxloper_));
                break;

            case xltypeMissing:
            case xltypeErr:
            case xltypeNil:
                xlw::XlfOperImpl::MissingOrEmptyError(type, ErrorId, "Conversion to unsigned long");
                throw XlfNeverGetHere();
                break;

            default:
                break;
            }
            OperType stackMem;
            int xlret = OperProps::coerce(lpxloper_, xltypeNum, &stackMem);
            if(xlret == xlretSuccess)
            {
                XlfOper<LPOPER_TYPE> result(&stackMem);
                return result.AsULong(ErrorId);
            }
            else
            {
                xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to unsigned long");
                throw XlfNeverGetHere();
            }
        }

        //! Converts to a char * with error identifer.
        char* AsString(const char* ErrorId = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            if(type == xltypeStr)
            {
                return OperProps::getString(lpxloper_);
            }
            else
            {
                OperType stackMem;
                int xlret = OperProps::coerce(lpxloper_, xltypeStr, &stackMem);
                if(xlret == xlretSuccess)
                {
                    XlfOper<LPOPER_TYPE> result(&stackMem);
                    return result.AsString(ErrorId);
                }
                else
                {
                    xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to String");
                    throw XlfNeverGetHere();
                }
            }
        }

        //! Converts to a wstring.
        std::wstring AsWstring(const char* ErrorId = 0, int *pxlret = 0) const
        {
            XlTypeType type(OperProps::getXlType(lpxloper_) & 0xFFF);
            if(type == xltypeStr)
            {
                return OperProps::getWString(lpxloper_);
            }
            else
            {
                OperType stackMem;
                int xlret = OperProps::coerce(lpxloper_, xltypeStr, &stackMem);
                if(xlret == xlretSuccess)
                {
                    XlfOper<LPOPER_TYPE> result(&stackMem);
                    return result.AsWstring(ErrorId);
                }
                else
                {
                    xlw::XlfOperImpl::ThrowOnError(xlret, ErrorId, "Conversion to WString");
                    throw XlfNeverGetHere();
                }
            }
        }

        std::vector<double> AsDoubleVector(const char* ErrorId = 0, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional) const
        {
            std::vector<double> result;
            MultiRowType nbRows(OperProps::getRows(lpxloper_));
            MultiColType nbCols(OperProps::getCols(lpxloper_));

            bool isUniDimRange = ( nbRows == 1 || nbCols == 1 );
            if (policy == XlfOperImpl::UniDimensional && !isUniDimRange)
            {
                // not a vector we return a failure
                xlw::XlfOperImpl::ThrowOnError(xlretInvXloper, ErrorId, "Not unidemensional");
                throw XlfNeverGetHere();
            }

            result.resize(nbRows * nbCols);

            for(MultiRowType row(0); row < nbRows; ++row)
            {
                for(MultiRowType col(0); col < nbCols; ++col)
                {
                    XlfOper<LPOPER_TYPE> element(OperProps::getElement(lpxloper_, row, col));
                    if(policy == XlfOperImpl::RowMajor)
                    {
                        result[row * nbCols + col] = element.AsDouble(ErrorId);
                    }
                    else
                    {
                        result[col * nbRows + row] = element.AsDouble(ErrorId);
                    }
                }
            }
            return result;
        }

        MyArray AsArray(const char* ErrorId = 0, XlfOperImpl::DoubleVectorConvPolicy policy = XlfOperImpl::UniDimensional) const
        {
            MultiRowType nbRows(OperProps::getRows(lpxloper_));
            MultiColType nbCols(OperProps::getCols(lpxloper_));

            bool isUniDimRange = ( nbRows == 1 || nbCols == 1 );
            if (policy == XlfOperImpl::UniDimensional && !isUniDimRange)
            {
                // not a vector we return a failure
                xlw::XlfOperImpl::ThrowOnError(xlretInvXloper, ErrorId, "Not unidemensional");
                throw XlfNeverGetHere();
            }

            MyArray result(ArrayTraits<MyArray>::create(nbRows * nbCols));

            for(MultiRowType row(0); row < nbRows; ++row)
            {
                for(MultiRowType col(0); col < nbCols; ++col)
                {
                    XlfOper<LPOPER_TYPE> element(OperProps::getElement(lpxloper_, row, col));
                    if(policy == XlfOperImpl::RowMajor)
                    {
                        ArrayTraits<MyArray>::setAt(result, row * nbCols + col, element.AsDouble(ErrorId));
                    }
                    else
                    {
                        ArrayTraits<MyArray>::setAt(result, col * nbRows + row, element.AsDouble(ErrorId));
                    }
                }
            }
            return result;
        }

        MyMatrix AsMatrix(const char* ErrorId = 0) const
        {
            MultiRowType nbRows(OperProps::getRows(lpxloper_));
            MultiColType nbCols(OperProps::getCols(lpxloper_));
            MyMatrix result(MatrixTraits<MyMatrix>::create(nbRows, nbCols));
            for(MultiRowType row(0); row < nbRows; ++row)
            {
                for(MultiRowType col(0); col < nbCols; ++col)
                {
                    XlfOper<LPOPER_TYPE> element(OperProps::getElement(lpxloper_, row, col));
                    MatrixTraits<MyMatrix>::setAt(result, row, col, element.AsDouble(ErrorId));
                }
            }
            return result;
        }

        CellMatrix AsCellMatrix(const char* ErrorId = 0) const
        {
            if(IsMissing() || IsNil())
            {
                CellMatrix result(1,1);
                return result;
            }
            if(IsError())
            {
                CellMatrix result(1,1);
				result(0, 0)=CellValue::error_type( OperProps::getError(lpxloper_));
                return result;
            }
            MultiRowType nbRows(OperProps::getRows(lpxloper_));
            MultiColType nbCols(OperProps::getCols(lpxloper_));
            CellMatrix result(nbRows, nbCols);
            for(MultiRowType row(0); row < nbRows; ++row)
            {
                for(MultiRowType col(0); col < nbCols; ++col)
                {
                    XlfOper<LPOPER_TYPE> element(OperProps::getElement(lpxloper_, row, col));
                    if(element.IsNumber())
                    {
                        result(row, col) = element.AsDouble(ErrorId);
                    }
                    else if(element.IsString())
                    {
                        result(row, col) = element.AsWstring(ErrorId);
                    }
                    else if(element.IsBool())
                    {
                        result(row, col) = element.AsBool(ErrorId);
                    }
                    else if(element.IsInt())
                    {
                        result(row, col) = element.AsInt(ErrorId);
                    }
                    else if(element.IsError())
                    {
						result(row, col) = CellValue::error_type(OperProps::getError(element.lpxloper_));
                    }
                    else if(element.IsNil())
                    {
                        ; // do nothing
                    }
                    else
                    {
                        THROW_XLW("Unsupported type in CellMatrix conversion");
                    }
                }
            }
            return result;
        }

        //@}


        //! \name Set the value of the underlying reference
        //@{
        //! Set the underlying XLOPER * to lpxloper.
        void Set(LPOPER_TYPE lpxloper)
        {
            OperProps::copy(lpxloper, lpxloper_);
        }
        //! Set to a string.value
        void Set(const std::string& value)
        {
            OperProps::setString(lpxloper_, value);
        }
        //! Set to a wide string.value
        void Set(const std::wstring& value)
        {
            OperProps::setWString(lpxloper_, value);
        }
        //! Set to a double
        void Set(double value)
        {
            OperProps::setDouble(lpxloper_, value);
        }
        //! Set to a short
        void Set(short value)
        {
            OperProps::setInt(lpxloper_, value);
        }
        //! Set to an int
        void Set(int value)
        {
            OperProps::setInt(lpxloper_, value);
        }
        //! Set to an unsigned long
        void Set(unsigned long value)
        {
            OperProps::setDouble(lpxloper_, static_cast<double>(value));
        }
        //! Set to a bool
        void Set(bool value)
        {
            OperProps::setBool(lpxloper_, value);
        }
        //! Set to a c string
        void Set(const char *value)
        {
            OperProps::setString(lpxloper_, value);
        }
        //! Set to a c wide string
        void Set(const wchar_t* value)
        {
            OperProps::setWString(lpxloper_, value);
        }
        void Set(const CellMatrix& cells)
        {
            XlfOper<LPOPER_TYPE> temp(cells);
            std::swap(temp, *this);
        }
        void Set(const MyMatrix& matrix)
        {
            XlfOper<LPOPER_TYPE> temp(matrix);
            std::swap(temp, *this);
        }
        void Set(const MyArray& values)
        {
            XlfOper<LPOPER_TYPE> temp(values);
            std::swap(temp, *this);
        }
        void Set(const XlfRef& range)
        {
            XlfOper<LPOPER_TYPE> temp(range);
            std::swap(temp, *this);
        }
        //! Set to an error code
        void SetError(ErrorType errorCode)
        {
            OperProps::setError(lpxloper_, errorCode);
        }
        //@}

        //! \name Equality operators
        //@{
        //! equals operator from same type
        XlfOper<LPOPER_TYPE>& operator=(const XlfOper<LPOPER_TYPE>& rhs)
        {
            OperProps::copy(rhs.lpxloper_, lpxloper_);
            return *this;
        }

        //! equals operator from a pointer to the same type
        XlfOper<LPOPER_TYPE>& operator=(const LPOPER_TYPE rhs)
        {
            OperProps::copy(rhs, lpxloper_);
            return *this;
        }

        //! equals operator from double
        XlfOper<LPOPER_TYPE>& operator=(double rhs)
        {
            OperProps::setDouble(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from bool
        XlfOper<LPOPER_TYPE>& operator=(bool rhs)
        {
            OperProps::setBool(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from int
        XlfOper<LPOPER_TYPE>& operator=(int rhs)
        {
            OperProps::setInt(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from unsigned long
        XlfOper<LPOPER_TYPE>& operator=(unsigned long rhs)
        {
            OperProps::setDouble(lpxloper_, static_cast<double>(rhs));
            return *this;
        }

        //! equals operator from string
        XlfOper<LPOPER_TYPE>& operator=(const std::string& rhs)
        {
            OperProps::setString(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from wide string
        XlfOper<LPOPER_TYPE>& operator=(const std::wstring& rhs)
        {
            OperProps::setWString(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from c string
        XlfOper<LPOPER_TYPE>& operator=(const char* rhs)
        {
            OperProps::setString(lpxloper_, rhs);
            return *this;
        }

        //! equals operator from wide c string
        XlfOper<LPOPER_TYPE>& operator=(const wchar_t* rhs)
        {
            OperProps::setWString(lpxloper_, rhs);
            return *this;
        }
        //@}
    };

} }

#endif

