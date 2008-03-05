
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

#ifndef INC_XlfOper4_H
#define INC_XlfOper4_H

/*!
\file XlfOper4.h
\brief Class XlfOper4 - Wrapper around a pointer to the XLOPER Excel 4 data structure
*/

// $Id: XlfOper4.h 340 2007-10-14 15:40:31Z ericehlers $

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

namespace xlw {

    class XlfRef;
    class CellMatrix;

    //! Wrapper around a pointer to the XLOPER Excel 4 data structure.
    /*!
    XlfOper4 holds a pointer to the XLOPER datatype used by Excel 4.  This class
    should be used for applications which are written specifically for Excel 4.
    The compiled addin will be recognized by Excel 12, but will retain its Excel 4
    behavior, not picking up any of the enhanced functionality of Excel 12.

    The interface for this class is otherwise the same as that for class XlfOper.
    */
    class EXCEL32_API XlfOper4
    {
    public:

        XlfOper4();
        XlfOper4(const XlfOper4& oper);
        XlfOper4(LPXLOPER lpxloper);
        XlfOper4(double value);
        XlfOper4(short value);
        XlfOper4(short value, bool Error);
        XlfOper4(bool value);
        XlfOper4(const char *value);
        XlfOper4(const std::string& value);
        XlfOper4(const CellMatrix& value);
        XlfOper4(const MyMatrix& value);
        XlfOper4(const MyArray& value);
        XlfOper4(const XlfRef& range);
        template <class FwdIt>
        XlfOper4(WORD rows, BYTE cols, FwdIt start)
        {
            Allocate();
            Set(rows,cols,start);
        }
        static XlfOper4 Error(WORD);
        ~XlfOper4();

        void FreeAuxiliaryMemory() const;

        XlfOper4& operator=(const XlfOper4& xloper);
        operator LPXLOPER();

        bool IsMissing() const;
        bool IsError() const;
        bool IsRef() const;
        bool IsSRef() const;
        bool IsMulti() const;
        bool IsNumber() const;
        bool IsString() const;
        bool IsNil() const;
        bool IsBool() const;
        bool IsInt() const;
        WORD xltype() const;

        double AsDouble(int * pxlret = 0) const;
        double AsDouble(const std::string& ErrorId, int * pxlret = 0) const;
        enum DoubleVectorConvPolicy
        {
            UniDimensional,
            RowMajor,
            ColumnMajor
        };
        std::vector<double> AsDoubleVector(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
        std::vector<double> AsDoubleVector(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
        MyArray AsArray(DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
        MyArray AsArray(const std::string& ErrorId,DoubleVectorConvPolicy policy = UniDimensional, int * pxlret = 0) const;
        short AsShort(int * pxlret = 0) const;
        short AsShort(const std::string& ErrorId, int * pxlret = 0) const;
        bool AsBool(int * pxlret = 0) const;
        bool AsBool(const std::string& ErrorId,int * pxlret = 0) const;
        int AsInt(int * pxlret = 0) const;
        int AsInt(const std::string& ErrorId,int * pxlret = 0) const;
        char * AsString(int * pxlret = 0) const;
        char * AsString(const std::string& ErrorId,int * pxlret = 0) const;
        CellMatrix AsCellMatrix( int * pxlret=0) const;
        CellMatrix AsCellMatrix( const std::string& ErrorId,int * pxlret=0) const;
        MyMatrix AsMatrix( int * pxlret=0) const;
        MyMatrix AsMatrix( const std::string& ErrorId,int * pxlret=0) const;
        XlfRef AsRef(int * pxlret = 0) const;
        LPXLOPER GetLPXLOPER() const;

        XlfOper4& Set(LPXLOPER lpxloper);
        XlfOper4& Set(double value);
        XlfOper4& Set(short value);
        XlfOper4& Set(bool value);
        XlfOper4& Set(const char *value);
        XlfOper4& Set(const CellMatrix& cells);
        XlfOper4& Set(const MyMatrix& matrix);
        XlfOper4& Set(const MyArray& values);
        XlfOper4& Set(const XlfRef& range);
        XlfOper4& Set(short value, bool Error);
        XlfOper4& SetError(WORD error);
        template<class FwdIt>
        XlfOper4& Set(WORD r, BYTE c, FwdIt it)
        {
            lpxloper_->xltype = xltypeMulti;
            lpxloper_->val.array.rows = r;
            lpxloper_->val.array.columns = c;
            lpxloper_->val.array.lparray = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));
            for (size_t i = 0; i < size_t(r*c); ++i, ++it)
                lpxloper_->val.array.lparray[i] = *(LPXLOPER)XlfOper4(*it);
            return *this;
        }

    private:
        LPXLOPER lpxloper_;

        int Coerce(short type, XlfOper4& result) const;
        int Allocate();
        void Deallocate();

        static int xlbitFreeAuxMem;

        int ThrowOnError(int) const;
        int ThrowOnError(int, const std::string& identifier) const;

        int ConvertToDoubleVector(std::vector<double>&, DoubleVectorConvPolicy policy = UniDimensional) const;
        int ConvertToDouble(double&) const throw();
        int ConvertToShort(short&) const throw();
        int ConvertToBool(bool&) const throw();
        int ConvertToInt(int&) const throw();
        int ConvertToString(char *&) const throw();
        int ConvertToCellMatrix( CellMatrix& output) const;
        int ConvertToMatrix( MyMatrix& output) const;
        int ConvertToRef(XlfRef&) const throw();
        int XlfOper4::ConvertToErr(WORD& e) const throw();

        friend class XlfExcel;
    };

}

#ifdef NDEBUG
#include <xlw/XlfOper4.inl>
#endif

#endif

