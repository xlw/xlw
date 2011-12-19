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

#include <xlw/IXlfOperShared.h>

namespace xlw { namespace impl {

    template <>
    struct XlfOperProperties<LPXLFOPER>
    {
        static IXlfOperShared* m_version;
        static void setExcel12(bool isExcel12);
        static void clearMemory();
        typedef int ErrorType;
        typedef int IntType;
        typedef RW MultiRowType;
        typedef COL MultiColType;
        typedef DWORD XlTypeType;
        typedef XLFOPER OperType;

        static XlTypeType getXlType(LPXLFOPER oper)
        {
            return m_version->getXlType(oper);
        }
        static void setXlType(LPXLFOPER oper, XlTypeType newValue)
        {
            m_version->setXlType(oper, newValue);
        }
        static double getDouble(LPXLFOPER oper)
        {
            // optimization: since the position of the double value is always in
            // the same place we can avoid a level of indirection for this operation
            // confirmed working across all bitnesses and compilers
            return oper->oper4.val.num;
        }
        static void setDouble(LPXLFOPER oper, double newValue)
        {
            m_version->setDouble(oper, newValue);
        }
        static IntType getInt(LPXLFOPER oper)
        {
            return m_version->getInt(oper);
        }
        static void setInt(LPXLFOPER oper, IntType newValue)
        {
            m_version->setInt(oper, newValue);
        }
        static bool getBool(LPXLFOPER oper)
        {
            return m_version->getBool(oper);
        }
        static void setBool(LPXLFOPER oper, bool newValue)
        {
            m_version->setBool(oper, newValue);
        }
        static ErrorType getError(LPXLFOPER oper)
        {
            return m_version->getError(oper);
        }
        static void setError(LPXLFOPER oper, ErrorType newValue)
        {
            m_version->setError(oper, newValue);
        }
        static RW getRows(LPXLFOPER oper)
        {
            return m_version->getRows(oper);
        }
        static void setArraySize(LPXLFOPER oper, RW rows, COL cols)
        {
            return m_version->setArraySize(oper, rows, cols);
        }
        static COL getCols(LPXLFOPER oper)
        {
            return m_version->getCols(oper);
        }
        static LPXLFOPER getElement(LPXLFOPER oper, RW row, COL column)
        {
            return m_version->getElement(oper, row, column);
        }
        static char* getString(LPXLFOPER oper)
        {
            return m_version->getString(oper);
        }
        static void setString(LPXLFOPER oper, const std::string& newValue)
        {
            m_version->setString(oper, newValue);
        }
        static std::wstring getWString(LPXLFOPER oper)
        {
            return m_version->getWString(oper);
        }
        static void setWString(LPXLFOPER oper, const std::wstring& newValue)
        {
            m_version->setWString(oper, newValue);
        }
        static XlfRef getRef(LPXLFOPER oper)
        {
            return m_version->getRef(oper);
        }
        static void setRef(LPXLFOPER oper, const XlfRef& newValue)
        {
            m_version->setRef(oper, newValue);
        }
        static int coerce(LPXLFOPER fromOper, DWORD toType, LPXLFOPER toOper)
        {
            return m_version->coerce(fromOper, toType, toOper);
        }
        static void XlFree(LPXLFOPER oper)
        {
            m_version->XlFree(oper);
        }
        static void copy(LPXLFOPER fromOper, LPXLFOPER toOper)
        {
            m_version->copy(fromOper, toOper);
        }
        static void copyUsingNew(LPXLFOPER fromOper, LPXLFOPER toOper)
        {
            m_version->copyUsingNew(fromOper, toOper);
        }
        static void freeCreatedUsingNew(LPXLFOPER oper)
        {
            m_version->freeCreatedUsingNew(oper);
        }
    };

} }