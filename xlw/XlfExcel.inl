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
#include <xlw/XlfException.h>
#include <xlw/macros.h>
#include <iostream>

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
INLINE void XlfExcel::FreeMemory(bool finished)
{
  size_t nbBuffersToKeep = 1;
  if (finished)
    nbBuffersToKeep = 0;
  while (freeList_.size() > nbBuffersToKeep)
  {
    delete[] freeList_.back().start;
    freeList_.pop_back();
  }
  offset_ = 0;
}

INLINE void XlfExcel::PushNewBuffer(size_t size)
{
  XlfBuffer newBuffer;
  newBuffer.size = size;
  newBuffer.start = new char[size];
  freeList_.push_front(newBuffer);
  offset_=0;
#if !defined(NDEBUG)
	std::cerr << __HERE__ << "xlw is allocating a new buffer of " << size << " bytes" << std::endl;
#endif
  return;
}

/*!
\param bytes is the size of the chunk required in bytes.
\return the address of the chunk.
 
Check if the buffer has enough memory, and move the offset of the static
buffer of the ammount of memory requested.
 
\bug If the buffer is full, it can't be extended and an exception
XlfBufferIsFull is thrown.
*/
INLINE LPSTR XlfExcel::GetMemory(size_t bytes)
{
  if (freeList_.empty())
    PushNewBuffer(1024);
  while (1)
  {
    XlfBuffer& buffer = freeList_.front();
    if (offset_ + bytes < buffer.size)
    {
      int temp = offset_;
      offset_ += bytes;
      return buffer.start + temp;
    }
    else
      PushNewBuffer(buffer.size*2);
  }
  // should never get to this point...
  return 0;
}
