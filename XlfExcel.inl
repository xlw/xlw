// Copyright (c) 1998-2001
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

/*!
\file XlfExcel.inl
\brief Implements inline methods of XlfExcel.
*/

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif
#include "ERR_Macros.h"
#include "XlfException.h"

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
	
  if (bufsz_ < offset_ + bytes)
  	ERR_THROW(XlfExceptionBufferFull);
	offset_ += bytes;
	return buffer_ + temp;
}
