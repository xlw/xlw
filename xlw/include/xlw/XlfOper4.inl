
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

/*!
\file XlfOper4.inl
\brief Implements inline methods of XlfOper4.
*/

// $Id: XlfOper4.inl 274 2006-07-13 13:55:08Z nando $

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

namespace xlw {

    INLINE XlfOper4::XlfOper4()
    {
        Allocate();
    }

    INLINE XlfOper4::XlfOper4(const XlfOper4& oper)
    {
        *this = oper;
    };

    INLINE XlfOper4::XlfOper4(double value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(short value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(short value, bool error)
    {
        Allocate();
        Set(value,error);
    }

    INLINE XlfOper4::XlfOper4(bool value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(const char *value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(const std::string& value)
    {
        Allocate();
        Set(value.c_str());
    }

    INLINE XlfOper4::XlfOper4(const CellMatrix& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(const MyMatrix& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(const MyArray& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper4::XlfOper4(const XlfRef& range)
    {
        Allocate();
        Set(range);
    }

    INLINE XlfOper4::XlfOper4(WORD rows, WORD cols) {
        Allocate();
        Set(rows, cols);
    }

    INLINE XlfOper4 XlfOper4::Error(WORD xlerr)
    {
        //static XLOPER oper;
        //XlfOper4 ret(&oper);
        // The above is not thread safe.
        XlfOper4 ret;
        ret.SetError(xlerr);
        return ret;
    }

    INLINE XlfOper4& XlfOper4::operator=(const XlfOper4& rhs)
    {
        if (this != &rhs)
            lpxloper_ = rhs.lpxloper_;
        return *this;
    }

    INLINE XlfOper4::operator LPXLOPER()
    {
        return lpxloper_;
    }

    INLINE bool XlfOper4::IsMissing() const
    {
        return lpxloper_->xltype & xltypeMissing;
    }

    INLINE bool XlfOper4::IsError() const
    {
        return lpxloper_->xltype & xltypeErr;
    }

    INLINE bool XlfOper4::IsRef() const
    {
        return lpxloper_->xltype & xltypeRef;
    }

    INLINE bool XlfOper4::IsSRef() const
    {
        return lpxloper_->xltype & xltypeSRef;
    }

    INLINE bool XlfOper4::IsMulti() const
    {
        return lpxloper_->xltype & xltypeMulti;
    }

    INLINE bool XlfOper4::IsNumber() const
    {
        return lpxloper_->xltype & xltypeNum;
    }

    INLINE bool XlfOper4::IsString() const
    {
        return lpxloper_->xltype & xltypeStr;
    }

    INLINE bool XlfOper4::IsNil() const
    {
        return lpxloper_->xltype & xltypeNil;
    }

    INLINE bool XlfOper4::IsBool() const
    {
        return lpxloper_->xltype & xltypeBool;
    }

    INLINE bool XlfOper4::IsInt() const
    {
        return lpxloper_->xltype & xltypeInt;
    }

    INLINE int XlfOper4::AsInt(int * pxlret) const
    {
        return static_cast<int>(AsDouble(pxlret));
    }

    INLINE LPXLOPER XlfOper4::GetLPXLOPER() const
    {
        return lpxloper_;
    }

    INLINE void XlfOper4::Deallocate()
    {}

}
