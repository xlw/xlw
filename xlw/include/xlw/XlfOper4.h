
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
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

#ifndef INC_XlfOper4_H
#define INC_XlfOper4_H

/*!
\file XlfOper4.h
\brief Class XlfOper4 - Wrapper around a pointer to the XLOPER Excel 4 data structure
*/

// $Id$

#include <xlw/XlfOperImpl.h>

#if defined(_MSC_VER)
#pragma once
#endif


namespace xlw {

    //! Wrapper around a pointer to the XLOPER Excel 4 data structure.
    /*!
    XlfOper4 holds a pointer to the XLOPER datatype used by Excel 4.  This class
    should be used for applications which are written specifically for Excel 4.
    The compiled addin will be recognized by Excel 12, but will retain its Excel 4
    behavior, not picking up any of the enhanced functionality of Excel 12.

    The interface for this class is otherwise the same as that for class XlfOper.
    */
    typedef xlw::impl::XlfOper<LPXLOPER> XlfOper4;

}

#endif

