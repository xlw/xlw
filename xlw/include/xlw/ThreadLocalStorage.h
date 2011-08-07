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


#ifndef INC_ThreadLocalStorage_H
#define INC_ThreadLocalStorage_H

#include <xlw/XlfWindows.h>
#include <xlw/XlfException.h>

/*!
\file ThreadLocalStorage.h
\brief Declares class CriticalSection and ProtectInScope
*/

// $Id$

namespace xlw {

// This is essential a smart pointer .. when
// thinking in terms of resource allocation
template<typename T>
class ThreadLocalStorage
{
public:
    ThreadLocalStorage()
    {
        m_tlsIndex = TlsAlloc();
        if(m_tlsIndex == TLS_OUT_OF_INDEXES)
        {
            THROW_XLW("TLS run out of TLS indices");
        }
    }

    ~ThreadLocalStorage()
    {
        TlsFree(m_tlsIndex);
    }

    T* GetValue()
    {
        return reinterpret_cast<T*>(TlsGetValue(m_tlsIndex));
    }
    void SetValue(T* newValue)
    {
        TlsSetValue(m_tlsIndex, reinterpret_cast<void*>(newValue));
    }

private:
    ThreadLocalStorage(const ThreadLocalStorage &);
    ThreadLocalStorage & operator=(const ThreadLocalStorage&);
    DWORD m_tlsIndex;
};

}

#endif
