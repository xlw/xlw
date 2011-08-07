
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfException_H
#define INC_XlfException_H

/*!
\file XlfException.h
\brief Class XlfException - Excel emergency exceptions
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

#if defined(_MSC_VER)
#pragma once
#endif

#define XLW__HERE__ __FILE__ "(" _MAKESTRING(__LINE__) "): "
#define _MAKESTRING(a) __MAKESTRING(a)
#define __MAKESTRING(a) #a

namespace xlw {

    //! Excel emergency exceptions
    /*!
    It is important to distinguish exceptions thrown as XlfException
    from others because they will be caught differently by the wrapper.
    See EXCEL_END.

    \warning These exceptions don't necessarly correspond to errors, see
    for example XlfExceptionUncalculated.

    \sa ThrowOnError
    */
    class EXCEL32_API XlfException : public std::exception
    {
    private:
        std::string what_;
    public:
        //! Message string ctor.
        XlfException(const std::string& what = "") : what_(what) {};
        //! std::exception interface
        const char* what () const throw () { return what_.c_str(); }
        //! the automatically generated destructor would not have the throw specifier.
        ~XlfException () throw () {}
    };

    //! Argument cell not calculated.
    /*!
    A cell was requested whose value has been invalidated.

    When it occurs, the framework should return immediately
    to excel to let it calculate the cell. Excel will then
    call again the function immediately after the argument
    was re-calculated.

    No message is passed to XlfException to speed up return
    to MS Excel.
    */
    class EXCEL32_API XlfExceptionUncalculated: public XlfException
    {};

    //! Abort requested.
    /*!
    Usually thrown by the user after XlfExcel::IsEscPressed had return true.
    */
    class EXCEL32_API XlfExceptionAbort: public XlfException
    {
    public:
        XlfExceptionAbort(): XlfException("abort") {}
    };

    //! Stack overflow.
    class EXCEL32_API XlfExceptionStackOverflow: public XlfException
    {
    public:
        XlfExceptionStackOverflow(): XlfException("stack overflow") {}
    };

    //! Never get here, allows us to tell the compiler that we should have exited already
    class EXCEL32_API XlfNeverGetHere: public std::runtime_error
    {
    public:
        XlfNeverGetHere(): std::runtime_error("Reached a never get here point") {}
    };

    //! User attempted to access an array out of bounds
    class EXCEL32_API XlfOutOfBounds: public std::runtime_error
    {
    public:
        XlfOutOfBounds(): std::runtime_error("Out of bounds array access detected") {}
    };

    //! Other Xlw Exceptions
    /*!
        These error can be thrown from anywhere
        in the code.
        This is a proposal for replacing use of raw strings,
        std:strings, CellMatrix as exception types in the code
    */
    class XlfGeneralException : public std::runtime_error
    {
    public:
        XlfGeneralException(const std::string& what) :
                std::runtime_error(what)
        {
        }

        XlfGeneralException(const std::ostringstream& what) :
                std::runtime_error(what.str())
        {
        }
    };
}

//! Used to simplify the throwing of formatted exceptions
#define THROW_XLW(ERROR_MSG_PARTS) \
    do { \
        std::ostringstream ostr; \
        ostr << ERROR_MSG_PARTS; \
        std::cerr << XLW__HERE__ << ostr.str() << std::endl; \
        throw xlw::XlfGeneralException(ostr); \
    } while(0)

#endif

