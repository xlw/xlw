
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

#ifndef INC_XlfArgDesc_H
#define INC_XlfArgDesc_H

/*!
\file XlfArgDesc.h
\brief Class XlfArgDesc - Encapsulates the argument definition
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    //! Encapsulates the argument definition.
    /*!
    Stores the name, the type, and a comment line to be displayed in the function
    wizard.

    The type defaults to the XLOPER type corresponding to the version (4 or 12) of
    the running instance of Excel.

    \deprecated Consider using XLRegistration::Arg instead.
    */
    class EXCEL32_API XlfArgDesc
    {
    public:
        //! \name Structors
        //@{
        //! Default ctor.
        XlfArgDesc();
        //! Detailed ctor.
        XlfArgDesc(const std::string& name, const std::string& comment, const std::string& type="XLF_OPER");
        //! Dtor
        ~XlfArgDesc();
        //@}

        //! \name Get and set class properties
        //@{
        //! Set the name of the argument
        void SetName(const std::string& name);
        //! Get the name
        const std::string& GetName() const;
        //! Set the help string associated
        void SetComment(const std::string& comment);
        //! Get the comment string
        const std::string& GetComment() const;
        //! Get the argument type
        std::string GetType() const;
        //@}
    private:
        //! Name of the argument as it appears in Excel,
        std::string name_;
        //! Comment line associated to the comment (appears in function wizard).
        std::string comment_;
        //! Type of the argument (see Excel documentation).
        std::string type_;
        //! Controls the name is valid to be used properly by the function wizard.
        void CheckNameLength();
    };

}

#endif

