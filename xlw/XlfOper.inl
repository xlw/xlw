// Copyright (c) 1998-2002
// Jerome Lecomte
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation. This software is freely provided "as is" 
// without express or implied warranty.

/*!
\file XlfOper.inl
\brief Implements inline methods of XlfOper.
*/

// $Id$

#ifdef NDEBUG
#define INLINE inline
#else
#define INLINE
#endif

/*! 
Calls Allocate 
*/
INLINE XlfOper::XlfOper()
{ 
  Allocate(); 
}

INLINE XlfOper::XlfOper(const XlfOper& oper)
{ 
  *this = oper; 
};

INLINE XlfOper::XlfOper(double value)
{ 
  Allocate(); 
  Set(value); 
}

INLINE XlfOper::XlfOper(short value)
{ 
  Allocate(); 
  Set(value); 
}

INLINE XlfOper::XlfOper(bool value)
{ 
  Allocate(); 
  Set(value); 
}

INLINE XlfOper::XlfOper(const char *value)
{ 
  Allocate(); 
  Set(value); 
}

INLINE XlfOper::XlfOper(const XlfRef& range)
{ 
  Allocate(); 
  Set(range); 
}

INLINE XlfOper& XlfOper::operator=(const XlfOper& rhs)
{ 
  if (this != &rhs)
    lpxloper_ = rhs.lpxloper_;
  return *this; 
}

INLINE XlfOper::operator LPXLOPER()
{ 
  return lpxloper_; 
}

INLINE bool XlfOper::IsMissing() const
{ 
  return lpxloper_->xltype == xltypeMissing; 
}

INLINE bool XlfOper::IsError() const
{ 
  return lpxloper_->xltype == xltypeErr;
}

INLINE int XlfOper::AsInt() const
{ 
  return static_cast<int>(AsDouble()); 
}

INLINE LPXLOPER XlfOper::GetLPXLOPER() const
{ 
  return lpxloper_; 
}

/*!
Do nothing. May be implemented later to avoid overload of the internal 
buffer by temporary XLOPER allocated by the XLL.
*/
INLINE void XlfOper::Deallocate()
{}
