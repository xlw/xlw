
/*
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
\file XlfMutex.h
\brief Implements struct for protecting critical sections.
*/

// $Id: XlfExcel.inl 474 2008-03-05 15:40:40Z ericehlers $

// Prevent CreateMutex() from being replaced by CreateMutexW()
// when wide character set is in use.
#include <TCHAR.h>

namespace xlw {

    //! Struct to protect critical sections.
    /*!
    This struct is specifically intended to protect unthreadsafe code which may
    be encountered during execution of a worksheet formula that has been
    registered with Excel as threadsafe ($).

    To protect a critical section, enclose it in a scope - e.g. a function
    scope, local scope, etc.  At the beginning of the scope, declare a variable
    of type XlfMutex on the stack.
    \code
    {                               // Begin scope
        XlfMutex xlfMutex;          // Acquire lock
        ...                         // Critical section (unthreadsafe code)
    }                               // End scope, lock released by ~XlfMutex()
    \endcode
    */

    struct XlfMutex {
        HANDLE hMutex;
        XlfMutex() {
            //hMutex = CreateMutex(NULL, FALSE, "xlw_mutex");
            hMutex = CreateMutex(NULL, FALSE, _T("xlw_mutex"));
            WaitForSingleObject(hMutex, INFINITE);
        }
        ~XlfMutex() {
            ReleaseMutex(hMutex);
        }
    };

}

