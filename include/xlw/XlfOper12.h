
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
\brief Class XlfOper12 - Wrapper around a pointer to the XLOPER Excel 12 data structure
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

namespace xlw {

    class CellMatrix;

    //! Wrapper around a pointer to the XLOPER12 Excel 12 data structure.
    /*!
    XlfOper12 holds a pointer to the XLOPER12 datatype used by Excel 12.  This
    class should be used for applications which are written specifically for Excel
    12.  The compiled addin will not be usable under Excel 4.

    The interface for this class is otherwise the same as that for class XlfOper.
    */
    class EXCEL32_API XlfOper12
    {
    public:
        XlfOper12();
        XlfOper12(const XlfOper12& oper);
        XlfOper12(LPXLOPER12 lpxloper);
        XlfOper12(double value);
        XlfOper12(short value);
        XlfOper12(short value, bool Error);
        XlfOper12(bool value);
        XlfOper12(const char *value);
        XlfOper12(const std::string& value);
        XlfOper12(const std::wstring& value);
        XlfOper12(const CellMatrix& value);
        XlfOper12(const MyMatrix& value);
        XlfOper12(const MyArray& value);
        XlfOper12(const XlfRef& range);
        XlfOper12(RW rows, COL cols);
        template <class FwdIt>
        XlfOper12(RW rows, COL cols, FwdIt start)
        {
            Allocate();
            Set(rows, cols, start);
        }
        static XlfOper12 Error(WORD);
        ~XlfOper12();

        void FreeAuxiliaryMemory() const;

        XlfOper12& operator=(const XlfOper12& xloper);
        XlfOper12 operator()(RW row, COL col);
        operator LPXLOPER12();

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

        RW rows() const;
        COL columns() const;

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
        std::wstring AsWstring(int * pxlret = 0) const;
        CellMatrix AsCellMatrix( int * pxlret=0) const;
        CellMatrix AsCellMatrix( const std::string& ErrorId,int * pxlret=0) const;
        MyMatrix AsMatrix( int * pxlret=0) const;
        MyMatrix AsMatrix( const std::string& ErrorId,int * pxlret=0) const;
        XlfRef AsRef(int * pxlret = 0) const;

        LPXLOPER12 GetLPXLOPER() const;

        XlfOper12& Set(LPXLOPER12 lpxloper);
        XlfOper12& Set(double value);
        XlfOper12& Set(short value);
        XlfOper12& Set(bool value);
        XlfOper12& Set(const char *value);
        XlfOper12& Set(const std::wstring &value);
        XlfOper12& Set(const CellMatrix& cells);
        XlfOper12& Set(const MyMatrix& matrix);
        XlfOper12& Set(const MyArray& values);
        XlfOper12& Set(const XlfRef& range);
        XlfOper12& Set(short value, bool Error);
        template<class FwdIt>
        XlfOper12& Set(RW r, COL c, FwdIt it)
        {
            lpxloper_->xltype = xltypeMulti;
            lpxloper_->val.array.rows = r;
            lpxloper_->val.array.columns = c;
            lpxloper_->val.array.lparray = (LPXLOPER12)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER12));
            for (size_t i = 0; i < size_t(r*c); ++i, ++it)
                lpxloper_->val.array.lparray[i] = *(LPXLOPER12)XlfOper12(*it);
            return *this;
        }
        XlfOper12& Set(RW r, COL c);
        XlfOper12& SetElement(RW r, COL c, const XlfOper12 &value);
        XlfOper12& SetError(WORD error);

        DWORD xltype() const;

    private:
        LPXLOPER12 lpxloper_;

        int Coerce(short type, XlfOper12& res) const;

        int Allocate();
        void Deallocate();

        int ThrowOnError(int) const;
        int ThrowOnError(int, const std::string& identifier) const;

        static int xlbitFreeAuxMem;

        int ConvertToDoubleVector(std::vector<double>&, DoubleVectorConvPolicy policy = UniDimensional) const;
        int ConvertToDouble(double&) const throw();
        int ConvertToShort(short&) const throw();
        int ConvertToBool(bool&) const throw();
        int ConvertToInt(int&) const throw();
        int ConvertToString(char *&) const throw();
        int ConvertToWstring(std::wstring &) const throw();
        int ConvertToCellMatrix( CellMatrix& output) const;
        int ConvertToMatrix( MyMatrix& output) const;
        int ConvertToRef(XlfRef&) const throw();
        int ConvertToErr(WORD& e) const throw();

        friend class XlfExcel;
    };

}

#ifdef NDEBUG
#include <xlw/XlfOper12.inl>
#endif

#endif

