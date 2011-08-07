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


#ifndef INC_CriticalSection_H
#define INC_CriticalSection_H

#include <xlw/XlfWindows.h>

/*!
\file CriticalSection.h
\brief Declares class CriticalSection and ProtectInScope
*/

// $Id$

namespace xlw {
//! Wrapper for a windows critical section
/*!
Create one of these objects for each time you
need to ensure that sections of cae cannot run at
the same time.

To be used in conjuction with the ProtectInScope class
*/
class CriticalSection
{
public:
    CriticalSection()
    {
        InitializeCriticalSection(&m_crit);
    }

    ~CriticalSection()
    {
        DeleteCriticalSection(&m_crit);
    }

    void lock()
    {
        EnterCriticalSection(&m_crit);
    }

    void unlock()
    {
        LeaveCriticalSection(&m_crit);
    }
private:
    CRITICAL_SECTION m_crit;
};

//! Helper for locking a critical section
/*!
Create in isntance of this object to protect
code from executing at the same time as other
code protected with the same critical section
object.
*/
class ProtectInScope
{
public:
    ProtectInScope(CriticalSection& criticalSection) :
        m_criticalSection(criticalSection)
    {

        m_criticalSection.lock();
    }

    ~ProtectInScope()
    {
        m_criticalSection.unlock();
    }
private:
    CriticalSection& m_criticalSection;
};

}
#endif
