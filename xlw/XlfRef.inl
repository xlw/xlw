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
\file XlfRef.inl
\brief Implements inline methods of class XlfRef.
*/

// $Id$

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

INLINE XlfRef::XlfRef()
    :rowbegin_(0), rowend_(0), colbegin_(0), colend_(0)
{}

INLINE XlfRef::XlfRef(WORD top, BYTE left, WORD bottom, BYTE right)
    :rowbegin_(top), rowend_(bottom + 1), colbegin_(left), colend_(right + 1)
{}

INLINE XlfRef::XlfRef(WORD row, BYTE col)
    :rowbegin_(row), rowend_(row + 1), colbegin_(col), colend_(col + 1)
{}

INLINE WORD XlfRef::GetRowBegin() const
{ 
  return rowbegin_; 
}

INLINE WORD XlfRef::GetRowEnd() const
{ 
  return rowend_; 
}

INLINE BYTE XlfRef::GetColBegin() const
{ 
  return colbegin_; 
}

INLINE BYTE XlfRef::GetColEnd() const
{
  return colend_; 
}

INLINE BYTE XlfRef::GetNbCols() const
{ 
  return colend_-colbegin_; 
}

INLINE WORD XlfRef::GetNbRows() const
{ 
  return rowend_-rowbegin_; 
}

INLINE void XlfRef::SetRowBegin(WORD rowbegin)
{ 
  rowbegin_ = rowbegin; 
}

INLINE void XlfRef::SetRowEnd(WORD rowend)
{ 
  rowend_ = rowend; 
}

INLINE void XlfRef::SetColBegin(BYTE colbegin)
{ 
  colbegin_ = colbegin; 
}

INLINE void XlfRef::SetColEnd(BYTE colend)
{ 
  colend_ = colend; 
}
