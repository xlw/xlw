/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte

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

// $Id$

#include <xlw/EXCEL32_API.h>
#include <string>
#ifdef PORT_USE_OLD_IO_HEADERS
#include <fstream.h>
#else
#include <fstream>
#include <list>
PORT_USING(std::ofstream);
#endif
#include <xlw/xlcall32.h>

#if defined(_MSC_VER)
#pragma once
#endif

//! Detroys the XlfExcel class when the module is terminated.
class XlfExcelDestroyer;

struct XlfBuffer 
{
  size_t size;
  char * start;
};

//! Interface between excel and the framework.
/*!
Implemented as a singleton (see \ref DP). You can't access the
ctors (private) and should access the class via the static
Instance() method.
*/
class EXCEL32_API XlfExcel
{
public:
  //! Used to obtain instance on XlfExcel object.
  static XlfExcel& Instance();
  //! Is the framework initialized ?
  static bool IsInitialized();
  //! Sends an Excel message box
  static void MsgBox(const char *, const char *title = 0);
  //! Sends a message in Excel status bar
  void SendMessage(const char * msg=0);
  //! Was the Esc key pressed ?
  bool IsEscPressed() const;
  //! Allocates memory in the framework temporary buffer
  LPSTR GetMemory(size_t bytes);
  //! Frees temporary memory used by the XLL
  void FreeMemory(bool finished=false);
  //! Gets XLL name
  std::string GetName() const;
  //! Interface to Excel (perform ERR_CHECKs before passing XlfOper to Excel)
#ifdef __MINGW32__
  int __cdecl Call(int xlfn, LPXLOPER pxResult, int count, ...) const;
#else
  int cdecl Call(int xlfn, LPXLOPER pxResult, int count, ...) const;
#endif
  //! Same as above but with an argument array instead of the variable length argument list
  int Callv(int xlfn, LPXLOPER pxResult, int count, LPXLOPER pxdata[]) const;
  //! Throws an exception when critical errors occur.
  int ThrowOnCriticalError(int) const;

private:
  //! Friendship for XlfExcelDestroyer allows it to call XlfExcel dtor.
  friend XlfExcelDestroyer;

  //! Static pointer to the unique instance of XlfExcel object.
  static XlfExcel *this_;
  //! Internal memory buffer holding memory to be referenced by Excel (excluded from the pimpl to allow inlining).
  std::list<XlfBuffer> freeList_;
  //! Pointer to next free aera (excluded from the pimpl to allow inlining).
  size_t offset_;
  //! Pointer to internal implementation (pimpl idiom, see \ref HS).
  struct XlfExcelImpl * impl_;

  //! Ctor.
  XlfExcel();
  //! Copy ctor is not defined.
  XlfExcel(const XlfExcel&);
  //! Assignment otor is not defined.
  XlfExcel& operator=(const XlfExcel&);
  //! Dtor is called by XlfExcelDestroyer when module is terminated.
  ~XlfExcel();
  //! Initialize the C++ framework.
  void InitLibrary();
  //! Creates a new static buffer and add it to the free list.
  void PushNewBuffer(size_t);
};

#ifdef NDEBUG
#include <xlw/XlfExcel.inl>
#endif

#endif