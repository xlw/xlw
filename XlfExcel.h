// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

#ifndef INC_XlfExcel_H
#define INC_XlfExcel_H

/*!
\file XlfExcel.h
\brief Declares class XlfExcel.
*/

#include "EXCEL32_API.h"
#include <string>
#ifdef PORT_USE_OLD_IO_HEADERS
#include <fstream.h>
#else
#include <fstream>
PORT_USING(std::ofstream);
#endif
#include "xlcall32.h"

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(DEBUG_HEADERS)
#pragma DEBUG_HEADERS
#endif

//! Detroys the XlfExcel class when the module is terminated.
class XlfExcelDestroyer;

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
  LPSTR GetMemory(int bytes);
  //! Frees all temporary memory used by the XLL
  void FreeMemory();
  //! Gets a pointer to the log file
  ofstream *GetLogFileHandle();
  //! Gets XLL name
  std::string GetName() const;
  //! Interface to Excel (perform ERR_CHECKs before passing XlfOper to Excel)
  int cdecl Call(int xlfn, LPXLOPER pxResult, int count, ...) const;
  //! Same as above but with an argument array instead of the variable length argument list
  int Callv(int xlfn, LPXLOPER pxResult, int count, LPXLOPER pxdata[]) const;
  //! Gets buffer occupation as an integer between 0 and 100
  double GetBufferOccupation() const;
  //! (Re)Allocates the buffer (destructive)
  void AllocateBuffer(size_t buffersize = 8192);

private:
  friend void ExcelLog(const char *str);
  //! Friendship for XlfExcelDestroyer allows it to call XlfExcel dtor.
  friend XlfExcelDestroyer;

  //! Static pointer to the unique instance of XlfExcel object.
  static XlfExcel *this_;
  //! Internal memory buffer holding memory to be referenced by Excel (excluded from the pimpl to allow inlining).
  char *buffer_;
  //! Size of the buffer (excluded from the pimpl to allow inlining).
  size_t bufsz_;
  //! Pointer to next free aera (excluded from the pimpl to allow inlining).
  int offset_;
  //! Pointer to internal implementation (pimpl idiom, see \ref HS).
  struct XlfExcelImpl * impl_;

  //! Ctor.
  XlfExcel();
  //! Copy ctor is not defined.
  XlfExcel(const XlfExcel&);
  //! Assignment otor is not defined.
  XlfExcel& operator=(const XlfExcel&);
  //! Initialize the C++ framework.
  void InitLibrary();
  //! Initialize log file.
  void InitLog();
  //! Log a string to the screen, to the file, or both.
  void Log(const char *str);
  //! Display a message box when the logging facilities are not initialized yet
  void EarlyLog(const char *msg);
  //! Dtor is called by XlfExcelDestroyer when module is terminated.
  ~XlfExcel();
};

#ifdef NDEBUG
#include "XlfExcel.inl"
#endif

#endif