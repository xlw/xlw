/*
 Copyright (C) 2011  John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_IXlfOperShared_H
#define INC_IXlfOperShared_H

/*!
\file IXlfoperShared.h
\brief defines interface for classes handling specific XLOPER versions
*/

// $Id$
#include <xlw/XlfExcel.h>
#include <xlw/XlfRef.h>

namespace xlw { namespace impl {

    class IXlfOperShared
    {
    public:
        virtual DWORD getXlType(LPXLFOPER oper) = 0;
        virtual void setXlType(LPXLFOPER oper, DWORD newValue) = 0;
        virtual void setDouble(LPXLFOPER oper, double newValue) = 0;
        virtual int getInt(LPXLFOPER oper) = 0;
        virtual void setInt(LPXLFOPER oper, int newValue) = 0;
        virtual bool getBool(LPXLFOPER oper) = 0;
        virtual void setBool(LPXLFOPER oper, bool newValue) = 0;
        virtual int getError(LPXLFOPER oper) = 0;
        virtual void setError(LPXLFOPER oper, int newValue) = 0;
        virtual RW getRows(LPXLFOPER oper) = 0;
        virtual void setArraySize(LPXLFOPER oper, RW rows, COL cols) = 0;
        virtual COL getCols(LPXLFOPER oper) = 0;
        virtual LPXLFOPER getElement(LPXLFOPER oper, RW row, COL column) = 0;
        virtual char* getString(LPXLFOPER oper) = 0;
        virtual void setString(LPXLFOPER oper, const std::string& newValue) = 0;
        virtual std::wstring getWString(LPXLFOPER oper) = 0;
        virtual void setWString(LPXLFOPER oper, const std::wstring& newValue) = 0;
        virtual XlfRef getRef(LPXLFOPER oper) = 0;
        virtual void setRef(LPXLFOPER oper, const XlfRef& newVlaue) = 0;
        virtual int coerce(LPXLFOPER fromOper, DWORD toType, LPXLFOPER toOper) = 0;
        virtual void XlFree(LPXLFOPER oper) = 0;
        virtual void copy(LPXLFOPER fromOper, LPXLFOPER toOper) = 0;
        virtual void copyUsingNew(LPXLFOPER fromOper, LPXLFOPER toOper) = 0;
        virtual void freeCreatedUsingNew(LPXLFOPER oper) = 0;
    };

} }

#endif
