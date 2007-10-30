
/*
 Copyright (C) 2007 Eric Ehlers
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
\file XlfOper.cpp
\brief Implements the XlfOper class.
*/

// $Id$

#include <xlw/XlfOper.h>
#include <xlw/XlfException.h>
#include <xlw/XlfRef.h>
#include <xlw/macros.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <xlw/CellMatrix.h>
#include <algorithm>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef NDEBUG
#include <xlw/XlfOper.inl>
#endif

/*!
This bit is currently unused by Microsoft Excel. We set it
to indicate that the LPXLOPER (passed by Excel) holds some extra
memory to be freed.
 
This bit is controled in ~XlfOper to know if the DLL should release
auxiliary memory or not by a call to FreeAuxiliaryMemory.
*/
int XlfOper::xlbitFreeAuxMem = 0x8000;

/*!
Attempts to convert the implict object to a double. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOper::ConvertToDouble.
*/
double XlfOper::AsDouble(int *pxlret) const
{
  double d;
  int xlret = ConvertToDouble(d);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return d;
};

double XlfOper::AsDouble(const std::string& ErrorId, int *pxlret) const
{
  double d;
  int xlret = ConvertToDouble(d);
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
MyArray XlfOper::AsArray(XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
	std::vector<double> tmp(AsDoubleVector(policy,pxlret));
	MyArray result(tmp.size());
	for (unsigned long i=0; i < result.size(); i++)
		result[i] = tmp[i];

	return result;
}

MyArray XlfOper::AsArray(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret ) const
{
	std::vector<double> tmp(AsDoubleVector(ErrorId,policy,pxlret));
	MyArray result(tmp.size());
	for (unsigned long i=0; i < result.size(); i++)
		result[i] = tmp[i];
	
	return result;
}


/*!
Attempts to convert the implict object to a vector of double. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOper::ConvertToDoubleVector.
*/
std::vector<double> XlfOper::AsDoubleVector(XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(v, policy);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return v;
}

std::vector<double> XlfOper::AsDoubleVector(const std::string& ErrorId, XlfOperImpl::DoubleVectorConvPolicy policy, int *pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(v, policy);
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

\sa XlfOper::ConvertToShort.
*/
short XlfOper::AsShort(int *pxlret) const
{
  short s;
  int xlret = ConvertToShort(s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

short XlfOper::AsShort(const std::string& ErrorId, int *pxlret) const
{
  short s;
  int xlret = ConvertToShort(s);
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

\sa XlfOper::ConvertToBool.
*/
bool XlfOper::AsBool(int *pxlret) const
{
  bool b;
  int xlret = ConvertToBool(b);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return b;
};

bool XlfOper::AsBool(const std::string& ErrorId, int *pxlret) const
{
  bool b;
  int xlret = ConvertToBool(b);
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

\sa XlfOper::ConvertToMatrix.
*/
MyMatrix XlfOper::AsMatrix(int *pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to matrix failed");
  return output;
}

MyMatrix XlfOper::AsMatrix(const std::string& ErrorId, int *pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(output);
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

\sa XlfOper::ConvertToCellMatrix.
*/
CellMatrix XlfOper::AsCellMatrix(int *pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to cell matrix failed");
  return output;
}

CellMatrix XlfOper::AsCellMatrix(const std::string& ErrorId, int *pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(output);
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

\sa XlfOper::ConvertToString.

The XLL allocates the memory on its own buffer. This buffer is automatically 
freed when a function of the XLL is called again. Note that coerce to
a char string is the slowest cast of all.
*/
char *XlfOper::AsString(int *pxlret) const
{
  char * s;
  int xlret = ConvertToString(s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

char *XlfOper::AsString(const std::string& ErrorId, int *pxlret) const
{
  char * s;
  int xlret = ConvertToString(s);
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

\sa XlfOper::ConvertToRef.
*/
XlfRef XlfOper::AsRef(int *pxlret) const
{
  XlfRef r;
  int xlret = ConvertToRef(r);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return r;
}

XlfOper& XlfOper::Set(const MyMatrix& values)
{
	if (values.rows() ==0 || values.columns() ==0)
	{
		return *this;
	}

	CellMatrix tmp(values.rows(), values.columns());
	for (unsigned long i=0; i < values.rows(); i++)
		for (unsigned long j=0; j < values.columns(); j++)
			tmp(i,j) = Element(values,i,j);
	return Set(tmp);
}

XlfOper& XlfOper::Set(const MyArray& values)
{
	if (values.size() ==0)
	{
		return *this;
	}
	CellMatrix tmp(static_cast<unsigned long>(values.size()), 1UL);
	for (unsigned long i=0; i < values.size(); i++)
			tmp(i,0) = values[i];
	return Set(tmp);
}

/*!
Throws an exception if the argument is anything other than xlretSuccess.
 
Events that require an immediate return to excel (uncalculated cell, abort,
stack overflow and invalid OPER (potential memory exhaustion)) throw an
XlfException.
 
Other events throw std::runtime_error.
*/
int XlfOper::ThrowOnError(int xlret) const
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
int XlfOper::ThrowOnError(int xlret, const std::string& Identifier) const
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
