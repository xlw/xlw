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

/*!
\file XlfExcel.inl
\brief Implements inline methods of XlfExcel.
*/

// $Id$

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif
#include <xlw/ERR_Macros.h>
#include <xlw/XlfException.h>

/*!
Since we pass XLOPER from the XLL towards
Excel we should not use XLL local variables: these would be
freed before MSExcel could get the data.

Therefore the framework C library that comes with Excel 97
developer's kit suggests to use a static area where the XlfOper
are stored (see XlfExcel::GetMemory) and still available to
Excel when we exit the XLL routine. This array is then reset
by a call to XlfExcel::FreeMemory at the begining of each new
call of one of the XLL functions.

The macro EXCEL_BEGIN includes a call to XlfExcel::FreeMemory.

\warning FreeMemory frees *all* memory previously allocated
by the framework.
*/
INLINE void XlfExcel::FreeMemory()
{
  offset_ = 0;
}

/*!
\param bytes is the size of the chunk required in bytes.
\return the address of the chunk.

Check if the buffer has enough memory, and move the offset of the static
buffer of the ammount of memory requested.

\bug If the buffer is full, it can't be extended and an exception
XlfBufferIsFull is thrown.
*/
INLINE LPSTR XlfExcel::GetMemory(int bytes)
{
	int temp = offset_;

  if (bufsz_ < size_t(offset_ + bytes))
  	ERR_THROW(XlfExceptionBufferFull);
	offset_ += bytes;
	return buffer_ + temp;
}
