
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 Narinder S Claire
 
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
\file XlfOper12.inl
\brief Implements inline methods of XlfOper12.
*/

// $Id: XlfOper12.inl 274 2006-07-13 13:55:08Z nando $

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

namespace xlw {

    INLINE XlfOper12::XlfOper12()
    {
        Allocate();
    }

    INLINE XlfOper12::XlfOper12(const XlfOper12& oper)
    {
        *this = oper;
    };

    INLINE XlfOper12::XlfOper12(double value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(short value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(short value, bool error)
    {
        Allocate();
        Set(value,error);
    }

    INLINE XlfOper12::XlfOper12(bool value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const char *value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const std::string& value)
    {
        Allocate();
        Set(value.c_str());
    }

    INLINE XlfOper12::XlfOper12(const std::wstring& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const CellMatrix& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const MyMatrix& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const MyArray& value)
    {
        Allocate();
        Set(value);
    }

    INLINE XlfOper12::XlfOper12(const XlfRef& range)
    {
        Allocate();
        Set(range);
    }

    INLINE XlfOper12::XlfOper12(RW rows, COL cols) {
        Allocate();
        Set(rows, cols);
    }

    INLINE XlfOper12 XlfOper12::Error(WORD xlerr)
    {
        //static XLOPER12 oper;
        //XlfOper12 ret(&oper);
        // The above is not thread safe.
        XlfOper12 ret;
        ret.SetError(xlerr);
        return ret;
    }

    INLINE XlfOper12& XlfOper12::operator=(const XlfOper12& rhs)
    {
        if (this != &rhs)
            lpxloper_ = rhs.lpxloper_;
        return *this;
    }

    INLINE XlfOper12::operator LPXLOPER12()
    {
        return lpxloper_;
    }

    INLINE bool XlfOper12::IsMissing() const
    {
		return (lpxloper_->xltype & xltypeMissing) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsError() const
    {
        return (lpxloper_->xltype & xltypeErr) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsRef() const
    {
        return (lpxloper_->xltype & xltypeRef) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsSRef() const
    {
        return (lpxloper_->xltype & xltypeSRef) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsMulti() const
    {
        return (lpxloper_->xltype & xltypeMulti) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsNumber() const
    {
        return (lpxloper_->xltype & xltypeNum) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsString() const
    {
        return (lpxloper_->xltype & xltypeStr) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsNil() const
    {
        return (lpxloper_->xltype & xltypeNil) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsBool() const
    {
        return (lpxloper_->xltype & xltypeBool) == 0 ? false : true ;
    }

    INLINE bool XlfOper12::IsInt() const
    {
        return (lpxloper_->xltype & xltypeInt) == 0 ? false : true ;
    }

    INLINE int XlfOper12::AsInt(int * pxlret) const
    {
        return static_cast<int>(AsDouble(pxlret));
    }

    INLINE LPXLOPER12 XlfOper12::GetLPXLOPER() const
    {
        return lpxloper_;
    }

    INLINE void XlfOper12::Deallocate()
    {}

}
