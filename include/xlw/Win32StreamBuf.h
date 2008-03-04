/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003 Jérôme Lecomte

 This file is part of xlw, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 xlw is free software: you can redistribute it and/or modify it under the
 terms of the xlw license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*!
 * \file Win32StreamBuf.h
 * \brief Class Win32StreamBuf - Forward stream to Win32 debugger
 * \ingroup utils
 */

// $Id$

#ifndef INC_Win32StreamBuf_H
#define INC_Win32StreamBuf_H

#include <streambuf>

//! Forwards stream to Win32 debugger.
/*!
Use iostream::rdbuf method to set Win32StreamBuf.
*/
class Win32StreamBuf: public std::streambuf
{
public:
    //! \name Structors and static members
    //@{
    Win32StreamBuf() {}
    ~Win32StreamBuf() {}
    //@}
protected:
    int_type overflow(int_type ch);
    int sync();

private:
    void SendToDebugWindow();
    std::string buf_;

    // not defined
    Win32StreamBuf(const Win32StreamBuf&);
    Win32StreamBuf& operator=(const Win32StreamBuf&);
};

#ifdef NDEBUG
#include "Win32StreamBuf.inl"
#endif

#endif // INC_Win32StreamBuf_H

