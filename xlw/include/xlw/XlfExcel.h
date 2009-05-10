
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


#ifndef INC_XlfExcel_H
#define INC_XlfExcel_H

/*!
\file XlfExcel.h
\brief Declares class XlfExcel.
*/

// $Id: XlfExcel.h 478 2008-03-06 11:43:12Z ericehlers $

#include <xlw/EXCEL32_API.h>
#include <xlw/xlcall32.h>
#include <list>
#include <map>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    //! Interpreted as LPXLOPER (Excel 4) or LPXLOPER12 (Excel 12).
    typedef void* LPXLFOPER;

    //! Interface between excel and the framework.
    /*!
    Implemented as a singleton (see \ref DP). You can't access the
    ctors (private) and should access the class via the static
    Instance() method.
    */
    class EXCEL32_API XlfExcel
    {
    public:
        //! \name Structors and static members
        //@{
        //! Used to obtain instance on XlfExcel object.
        static XlfExcel& Instance();
        //! Sends an Excel message box
        static void MsgBox(const char *, const char *title = 0);
        //! Dtor.
        ~XlfExcel();
        //@}

        //! \name Memory management
        //@{
        //! Allocates memory in the framework temporary buffer
        LPSTR GetMemory(size_t bytes);
        //! Frees temporary memory used by the XLL
        void FreeMemory(bool finished=false);
        //@}

        //! \name Inspectors
        //@{
        //! Gets XLL name
        std::string GetName() const;
        //@}

        /** \name Wrappers for Excel Call function
        Interface to Excel (perform ERR_CHECKs before passing XlfOper to Excel).\n
        The Call() functions accept a variable length argument list,
        the Callv() functions accept an argument array.
        */
        //@{
        //! Wrap the Call function for Excel version 4.
        int __cdecl Call4(int xlfn, LPXLOPER pxResult, int count, ...) const;
        //! Wrap the Call function for Excel version 12.
        int __cdecl Call12(int xlfn, LPXLOPER12 pxResult, int count, ...) const;
        //! Invoke Call4 or Call12 depending on which version of Excel is running.
        int __cdecl Call(int xlfn, LPXLFOPER pxResult, int count, ...) const;
        //! Wrap the Callv function for Excel version 4.
        int Call4v(int xlfn, LPXLOPER pxResult, int count, LPXLOPER pxdata[]) const;
        //! Wrap the Callv function for Excel version 12.
        int Call12v(int xlfn, LPXLOPER12 pxResult, int count, LPXLOPER12 pxdata[]) const;
        //! Invoke Callv4 or Callv12 depending on which version of Excel is running.
        int Callv(int xlfn, LPXLFOPER pxResult, int count, LPXLFOPER pxdata[]) const;
        //@}

        //! \name Wrappers for selected Excel operations
        //@{
        /*!
        Wrapped functions that are often needed and/or painful to code
        */
        //! Sends a message in Excel status bar.
        void SendMessage(const char * msg=0);
        //! Was the Esc key pressed ?
        bool IsEscPressed() const;
        //! Is the function being calculated currently called by the Function Wizard ?
        bool IsCalledByFuncWiz() const;
        //@}

        //! \name Information about the running version of Excel
        //@{
        //! Boolean differentiating Excel 12 (2007) from previous versions
        bool excel12() const { return excel12_; }
        //! The OPER type in use by this version of Excel
        std::string xlfOperType() const { return xlfOperType_; }
        //! The XLOPER type in use by this version of Excel
        std::string xlfXloperType() const { return xlfXloperType_; }
        //! The string type in use by this version of Excel
        std::string wStrType() const { return wStrType_; }
        //@}
    private:
        //! Static pointer to the unique instance of XlfExcel object.
        static XlfExcel *this_;

        //! Memory buffer used to store data that are passed to Excel
        /*!
        When we pass XLOPER from the XLL towards Excel we should not use
        XLL local variables as it would be freed before MSExcel could get
        the data.

        Therefore the framework C library that comes with \ref XLSDK97 "Excel
        97 developer's kit" suggests to use a static area where the XlfOper
        are stored (see XlfExcel::GetMemory) and still available to
        Excel when we exit the XLL routine. This array is then reset
        by a call to XlfExcel::FreeMemory at the begining of each new
        call of one of the XLL functions.

        \sa XlfExcel::GetMemory, XlfExcel::FreeMemory
        */
        struct XlfBuffer
        {
            //! Size of the buffer.
            size_t size;
            //! Start address.
            char * start;
        };

        //! A list of buffers.
        typedef std::list<XlfBuffer> BufferList;
        //! Internal memory buffer holding memory to be referenced by Excel (excluded from the pimpl to allow inlining).
        BufferList freeList_;
        //! Pointer to next free area (excluded from the pimpl to allow inlining).
        size_t offset_;

        //! Pointer to internal implementation (pimpl idiom, see \ref HS).
        struct XlfExcelImpl * impl_;

        //! Ctor.
        XlfExcel();
        //! Copy ctor is not defined.
        XlfExcel(const XlfExcel&);
        //! Assignment operator is not defined.
        XlfExcel& operator=(const XlfExcel&);
        //! Initialize the C++ framework.
        void InitLibrary();
        //! Create a new static buffer and add it to the free list.
        void PushNewBuffer(size_t);

        bool excel12_;
        std::string xlfOperType_;
        std::string xlfXloperType_;
        std::string wStrType_;
    };

}

#ifdef NDEBUG
#include <xlw/XlfExcel.inl>
#endif

#endif

