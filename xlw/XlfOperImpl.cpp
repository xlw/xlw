
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007 Eric Ehlers
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/XlfOperImpl.h>
#include <xlw/XlfException.h>
#include <xlw/XlfRef.h>
#include <xlw/macros.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <algorithm>

XlfOperImpl *XlfOperImpl::instance_ = 0;

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfOperImpl.inl>
#endif

/*!
This bit is currently unused by Microsoft Excel. We set it
to indicate that the LPXLOPER (passed by Excel) holds some extra
memory to be freed.
 
This bit is controled in ~XlfOper to know if the DLL should release
auxiliary memory or not by a call to FreeAuxiliaryMemory.
*/
int XlfOperImpl::xlbitFreeAuxMem = 0x8000;

const XlfOperImpl &XlfOperImpl::instance() {
    if (!instance_)
        throw("Attempt to reference uninitialized XlfOperImpl object");
    return *instance_;
}

/*!
Attempts to convert the implict object to a double. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOperImpl::ConvertToDouble.
*/
double XlfOperImpl::AsDouble(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  double d;
  int xlret = ConvertToDouble(xlfOperUnion, d);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return d;
};

double XlfOperImpl::AsDouble(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  double d;
  int xlret = ConvertToDouble(xlfOperUnion, d);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError( xlret,"Conversion to double " + ErrorId);
  return d;
};

/*!
Attempts to convert the implict object to a an array.
Does this by calling AsDoubleVector.
If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

*/
MyArray XlfOperImpl::AsArray(const XlfOperUnion &xlfOperUnion, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
	std::vector<double> tmp(AsDoubleVector(xlfOperUnion, policy, pxlret));
	MyArray result(tmp.size());
	for (unsigned long i=0; i < result.size(); i++)
		result[i] = tmp[i];

	return result;
}

MyArray XlfOperImpl::AsArray(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret ) const
{
	std::vector<double> tmp(AsDoubleVector(xlfOperUnion, ErrorId, policy, pxlret));
	MyArray result(tmp.size());
	for (unsigned long i=0; i < result.size(); i++)
		result[i] = tmp[i];
	
	return result;
}


/*!
Attempts to convert the implict object to a vector of double. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOperImpl::ConvertToDoubleVector.
*/
std::vector<double> XlfOperImpl::AsDoubleVector(const XlfOperUnion &xlfOperUnion, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(xlfOperUnion, v, policy);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return v;
}

std::vector<double> XlfOperImpl::AsDoubleVector(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(xlfOperUnion, v, policy);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId + " conversion to double vector");
  return v;
}

/*!
Attempts to convert the implict object to a short. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOperImpl::ConvertToShort.
*/
short XlfOperImpl::AsShort(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  short s;
  int xlret = ConvertToShort(xlfOperUnion, s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

short XlfOperImpl::AsShort(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  short s;
  int xlret = ConvertToShort(xlfOperUnion, s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret, ErrorId + " conversion to short failed");
  return s;
};

/*!
Attempts to convert the implict object to a bool. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOperImpl::ConvertToBool.
*/
bool XlfOperImpl::AsBool(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  bool b;
  int xlret = ConvertToBool(xlfOperUnion, b);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return b;
};

bool XlfOperImpl::AsBool(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  bool b;
  int xlret = ConvertToBool(xlfOperUnion, b);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId + " conversion to bool failed");
  return b;
};

/*!
Attempts to convert the implict object to a matrix. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOperImpl::ConvertToMatrix.
*/
MyMatrix XlfOperImpl::AsMatrix(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(xlfOperUnion, output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to matrix failed");
  return output;
}

MyMatrix XlfOperImpl::AsMatrix(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(xlfOperUnion, output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId + " conversion to matrix failed");
  return output;
}

/*!
Attempts to convert the implict object to a cell matrix. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOperImpl::ConvertToCellMatrix.
*/
CellMatrix XlfOperImpl::AsCellMatrix(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(xlfOperUnion, output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to cell matrix failed");
  return output;
}

CellMatrix XlfOperImpl::AsCellMatrix(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(xlfOperUnion, output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId + " conversion to cell matrix failed");
  return output;
}

/*!
Attempts to convert the implict object to a char string. If pxlret is not 
null the method won't throw and the Excel return code will be returned in 
this variable.

\sa XlfOperImpl::ConvertToString.

The XLL allocates the memory on its own buffer. This buffer is automatically 
freed when a function of the XLL is called again. Note that coerce to
a char string is the slowest cast of all.
*/
char *XlfOperImpl::AsString(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  char * s;
  int xlret = ConvertToString(xlfOperUnion, s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

char *XlfOperImpl::AsString(const XlfOperUnion &xlfOperUnion, const std::string& ErrorId, int *pxlret) const
{
  char * s;
  int xlret = ConvertToString(xlfOperUnion, s);
  if (pxlret)
    *pxlret=xlret;
  else
	  ThrowOnError(xlret,ErrorId + " conversion to char* failed");
  return s;
};

/*!
Attempts to convert the implict object to an XlfRef. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOperImpl::ConvertToRef.
*/
XlfRef XlfOperImpl::AsRef(const XlfOperUnion &xlfOperUnion, int *pxlret) const
{
  XlfRef r;
  int xlret = ConvertToRef(xlfOperUnion, r);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return r;
}

void XlfOperImpl::Set(XlfOperUnion &xlfOperUnion, const MyMatrix& values)
{
	if (values.rows() ==0 || values.columns() ==0)
	{
		return;
	}

	CellMatrix tmp(values.rows(), values.columns());
	for (unsigned long i=0; i < values.rows(); i++)
		for (unsigned long j=0; j < values.columns(); j++)
			tmp(i,j) = Element(values,i,j);
	Set(xlfOperUnion, tmp);
}

void XlfOperImpl::Set(XlfOperUnion &xlfOperUnion, const MyArray& values)
{
	if (values.size() ==0)
	{
		return;
	}
	CellMatrix tmp(static_cast<unsigned long>(values.size()), 1UL);
	for (unsigned long i=0; i < values.size(); i++)
			tmp(i,0) = values[i];
	Set(xlfOperUnion, tmp);
}

/*!
Throws an exception if the argument is anything other than xlretSuccess.
 
Events that require an immediate return to excel (uncalculated cell, abort,
stack overflow and invalid OPER (potential memory exhaustion)) throw an
XlfException.
 
Other events throw std::runtime_error.
*/
int XlfOperImpl::ThrowOnError(int xlret) const
{
  if (xlret == xlretSuccess)
    return xlret;

  if (xlret & xlretUncalced)
    throw XlfExceptionUncalculated();
  if (xlret & xlretAbort)
    throw XlfExceptionAbort();
  if (xlret & xlretStackOvfl)
    throw XlfExceptionStackOverflow();
  if (xlret & xlretInvXloper)
    throw XlfException("invalid OPER structure (memory could be exhausted)");
  if (xlret & xlretFailed)
    throw std::runtime_error("command failed");
  if (xlret & xlretInvCount)
    throw std::runtime_error("invalid number of arguments");
  if (xlret & xlretInvXlfn)
    throw std::runtime_error("invalid function number");
  // should never get there.
  assert(0);
  return xlret;
}

/*!
Throws an exception if the argument is anything other than xlretSuccess.
 
Events that require an immediate return to excel (uncalculated cell, abort,
stack overflow and invalid OPER (potential memory exhaustion)) throw an
XlfException.
 
Other events throw std::runtime_error. The Identifier is tagged on to the error message to help track down
problems. 
*/
int XlfOperImpl::ThrowOnError(int xlret, const std::string& Identifier) const
{
  if (xlret == xlretSuccess)
    return xlret;

  if (xlret & xlretUncalced)
    throw XlfExceptionUncalculated();
  if (xlret & xlretAbort)
    throw XlfExceptionAbort();
  if (xlret & xlretStackOvfl)
    throw XlfExceptionStackOverflow();
  if (xlret & xlretInvXloper)
    throw XlfException("invalid OPER structure (memory could be exhausted)," + Identifier);
  if (xlret & xlretFailed)
    throw std::runtime_error("command failed, " + Identifier);
  if (xlret & xlretInvCount)
    throw std::runtime_error("invalid number of argument, " + Identifier);
  if (xlret & xlretInvXlfn)
    throw std::runtime_error("invalid function number, " + Identifier);
  // should never get there.
  assert(0);
  return xlret;
}

/*!
Unlike other XlfOper, the return value is not allocated on the internal
buffer to avoid allocating more memory. Instead it is allocated on a
shared static XLOPER.

\arg error One of the values listed below and defined in xlcall32.h

\code
#define xlerrNull    0      // No info
#define xlerrDiv0    7		// Division by 0
#define xlerrValue   15		// Bad value
#define xlerrRef     23		// Bad reference
#define xlerrName    29		// Bad name
#define xlerrNum     36		// Bad number
#define xlerrNA      42		// Not available
\endcode

\sa XlfOper::SetError(WORD)
*/
XlfOper XlfOperImpl::Error(WORD xlerr)
{
	static XLOPER oper;
	XlfOper ret(&oper);
	ret.SetError(xlerr);
	return ret;
}
