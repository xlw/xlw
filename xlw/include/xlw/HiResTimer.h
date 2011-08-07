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


#ifndef INC_HiResTimer_H
#define INC_HiResTimer_H

#include <xlw/XlfWindows.h>

/*!
\file HiResTimer.h
\brief Declares class HiResTimer
*/

// $Id$

namespace xlw {
//! Wrapper for a windows High Resolution Timers functions
/*!
Create one of these objects for each time you
need to accurately time something.

Call elasped to get the time in number of seconds since the object
was created.

*/
class HiResTimer
{
public:
    HiResTimer();
    ~HiResTimer();
    double elapsed() const;
private:
    LARGE_INTEGER m_start;
};

}

#endif
