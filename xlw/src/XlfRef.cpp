/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
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
\file XlfRef.cpp
\brief Implements the XlfRef class.
*/

// $Id$

#include <xlw/XlfRef.h>
#include <sstream>

namespace
{
    std::string RowColToA1(RW row, COL col)
    {
        std::ostringstream ostr;
        COL colLeft = col;
        if(col > 26*26)
        {
            char colChar = 'A' + colLeft / (26 * 26) - 1;
            colLeft %= (26 * 26);
            ostr << colChar;
        }
        if(col > 26)
        {
            char colChar = 'A' + colLeft / 26 - 1;
            colLeft %= 26;
            ostr << colChar;
        }
        {
            char colChar = 'A' + colLeft;
            ostr << colChar;
        }
        ostr << row + 1;
        return ostr.str();
    }
}

namespace xlw
{
    std::string XlfRef::GetTextA1()
    {
        std::string result = RowColToA1(rowbegin_, colbegin_);
        if(colend_ > colbegin_ + 1 || rowend_ > rowbegin_ + 1)
        {
            result += ":";
            result += RowColToA1(rowend_ - 1, colend_ - 1);
        }
        return result;
    }

    std::string XlfRef::GetTextR1C1()
    {
        std::ostringstream ostr;
        ostr << "R" << rowbegin_ + 1 << "C" << colbegin_ + 1;
        if(colend_ > colbegin_ + 1 || rowend_ > rowbegin_ + 1)
        {
            ostr << ":" << "R" << rowend_ << "C" << colend_;
        }
        return ostr.str();
    }
}
