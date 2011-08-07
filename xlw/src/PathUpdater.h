
/*
 Copyright (C) 2009 Narinder S Claire
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


#ifndef INC_PathUpdater_H
#define INC_PathUpdater_H

/*!
\file PathUpdater.h
\brief Declares class PathUpdater.
*/

// $Id$

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    //! Adds the dll's directory to the path
    /*!
    Used to ensure that when LoadLibrary is called from
    within the dll the directory where the dll is is searched
    first. This behaviour is required by the .NET code
    */
    class PathUpdater
    {
    public:
        //! \name Structors and static members
        //@{
        //! Ctor.
        PathUpdater();
        //! Dtor.
        ~PathUpdater();
        //@}
    };
}

#endif
