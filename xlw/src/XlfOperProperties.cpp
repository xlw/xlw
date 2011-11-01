/*
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

/*!
\file XlfOperProperties.cpp
\brief Implements the singleton class that is used by XlfOper
*/

// $Id$

#include <xlw/XlfOperProperties.h>

namespace
{
    using namespace xlw::impl;
    using namespace xlw;

    template<class LPOPER_TYPE>
    class XlfOperSharedImpl : public IXlfOperShared
    {
        DWORD getXlType(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getXlType((LPOPER_TYPE)oper);
        }
        void setXlType(LPXLFOPER oper, DWORD newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setXlType((LPOPER_TYPE)oper, (typename XlfOperProperties<LPOPER_TYPE>::XlTypeType)newValue);
        }
        void setDouble(LPXLFOPER oper, double newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setDouble((LPOPER_TYPE)oper, newValue);
        }
        int getInt(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getInt((LPOPER_TYPE)oper);
        }
        void setInt(LPXLFOPER oper, int newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setInt((LPOPER_TYPE)oper, newValue);
        }
        bool getBool(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getBool((LPOPER_TYPE)oper);
        }
        void setBool(LPXLFOPER oper, bool newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setBool((LPOPER_TYPE)oper, newValue);
        }
        int getError(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getError((LPOPER_TYPE)oper);
        }
        void setError(LPXLFOPER oper, int newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setError((LPOPER_TYPE)oper, newValue);
        }
        RW getRows(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getRows((LPOPER_TYPE)oper);
        }
        void setArraySize(LPXLFOPER oper, RW rows, COL cols)
        {
            XlfOperProperties<LPOPER_TYPE>::setArraySize((LPOPER_TYPE)oper, rows, cols);
        }
        COL getCols(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getCols((LPOPER_TYPE)oper);
        }
        LPXLFOPER getElement(LPXLFOPER oper, RW row, COL column)
        {
            return (LPXLFOPER)XlfOperProperties<LPOPER_TYPE>::getElement((LPOPER_TYPE)oper, row, column);
        }
        char* getString(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getString((LPOPER_TYPE)oper);
        }
        void setString(LPXLFOPER oper, const std::string& newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setString((LPOPER_TYPE)oper, newValue);
        }
        std::wstring getWString(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getWString((LPOPER_TYPE)oper);
        }
        void setWString(LPXLFOPER oper, const std::wstring& newValue)
        {
            XlfOperProperties<LPOPER_TYPE>::setWString((LPOPER_TYPE)oper, newValue);
        }
        XlfRef getRef(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::getRef((LPOPER_TYPE)oper);
        }
        void setRef(LPXLFOPER oper, const XlfRef& newValue)
        {
            return XlfOperProperties<LPOPER_TYPE>::setRef((LPOPER_TYPE)oper, newValue);
        }
        int coerce(LPXLFOPER fromOper, DWORD toType, LPXLFOPER toOper)
        {
            return XlfOperProperties<LPOPER_TYPE>::coerce((LPOPER_TYPE)fromOper, (typename XlfOperProperties<LPOPER_TYPE>::XlTypeType)toType,(LPOPER_TYPE)toOper);
        }
        void XlFree(LPXLFOPER oper)
        {
            XlfOperProperties<LPOPER_TYPE>::XlFree((LPOPER_TYPE)oper);
        }
        void copy(LPXLFOPER fromOper, LPXLFOPER toOper)
        {
            return XlfOperProperties<LPOPER_TYPE>::copy((LPOPER_TYPE)fromOper, (LPOPER_TYPE)toOper);
        }
        void copyUsingNew(LPXLFOPER fromOper, LPXLFOPER toOper)
        {
            return XlfOperProperties<LPOPER_TYPE>::copyUsingNew((LPOPER_TYPE)fromOper, (LPOPER_TYPE)toOper);
        }
        void freeCreatedUsingNew(LPXLFOPER oper)
        {
            return XlfOperProperties<LPOPER_TYPE>::freeCreatedUsingNew((LPOPER_TYPE)oper);
        }
    };
}

xlw::impl::IXlfOperShared* xlw::impl::XlfOperProperties<LPXLFOPER>::m_version = 0;

void xlw::impl::XlfOperProperties<LPXLFOPER>::setExcel12(bool isExcel12)
{
    if(isExcel12)
    {
        m_version = new XlfOperSharedImpl<LPXLOPER12>;
    }
    else
    {
        m_version = new XlfOperSharedImpl<LPXLOPER>;
    }
}

void xlw::impl::XlfOperProperties<LPXLFOPER>::clearMemory()
{
    delete m_version;
    m_version = 0;
}


