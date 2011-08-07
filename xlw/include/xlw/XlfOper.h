
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009  Narinder S Claire
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

#ifndef INC_XlfOper_H
#define INC_XlfOper_H

/*!
\file XlfOper.h
\brief Class XlfOper - Wrapper for XLOPER/XLOPER12 Excel data structure
*/

// $Id$

#include <xlw/XlfOperImpl.h>

#if defined(_MSC_VER)
#pragma once
#endif

//! Namespace for the classes in the xlw (Excel Wrapper) library
/*!
xlw is a wrapper for the Excel C API.  xlw implements an object oriented interface
in support of Excel Addins implementing worksheet functions and menu commands.
*/
namespace xlw {

    //! Wrapper for XLOPER/XLOPER12 Excel data structure
    /*!
    Class XlfOper implements a sole data member, a union of LPXLOPER and
    LPXLOPER12.  XlfOper may be initialized with a value of type LPXLFOPER
    (void*) received from Excel.  XlfOper dereferences this pointer via the
    union, depending on which version of Excel is running: The value is
    interpreted as type LPXLOPER under Excel 4, and LPXLOPER12 under Excel 12.

    The logic to dereference LPXLOPER/LPXLOPER12 is implemented in class
    XlfOperImpl and XlfOper forwards all of its calls to XlfOperImpl.

    \warning It is important \e not to add any data members or virtual
    functions to this class.  The design of xlw relies on the fact that class
    XlfOper has the same size as LPXLOPER/LPXLOPER12, this assumption allows
    values of those types received from Excel to be interpreted by the library
    as instances of XlfOper.
    */
    typedef impl::XlfOper<LPXLFOPER> XlfOper;

}

#endif

