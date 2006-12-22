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
Shallow copy of a pointer to XLOPER.
\param lpxloper Pointer to XLOPER.
Excel or by the XLL (default is true).
*/
XlfOper::XlfOper(LPXLOPER lpxloper): lpxloper_(lpxloper)
{}

/*!
Calls Deallocate() to free the XLOPER allocated by the XLL. XLOPER allocated
by Excel remain under Excel responsability.
 
Calls FreeAuxiliaryMemory if the XLOPER is marked by XlfOper::Call as an 
XLOPER returned by MS Excel and if the type matches one of xltypeStr, 
xltypeRef, xltypeMulti, xltypeBigData.
*/
XlfOper::~XlfOper()
{
  if (! lpxloper_)
    return;

  int type = lpxloper_->xltype;

//  Only the types bellow can be flagged xlFreeAuxMem, thus the test is 
//  actually redundant: we don't need to re-check the type of the oper.
//  
//  bool canHaveAuxMem = (type & xltypeStr ||
//                        type & xltypeRef ||
//                        type & xltypeMulti ||
//                        type & xltypeBigData);
  if (type & xlbitFreeAuxMem)
  {
    // switch back the bit as it was originally
    lpxloper_->xltype &= ~xlbitFreeAuxMem;
    FreeAuxiliaryMemory();
  }
  Deallocate();
  return;
}

/*!
Allocates 16 bits (size of a XLOPER) on the temporary buffer
stored by XlfExcel with a call to XlfExcel::GetMemory().
 
\warning Each XlfOper allocation causes a call to Allocate which in turn
reserve the necessary number of bytes in the internal buffer. The
problem is that even temporary XlfOper used inside the xll function use
this internal buffer. This buffer is not freed before the next call to
the xll to ensure Excel can use the data before they are freed. This
causes a bottleneck if the function uses many temporary XlfOper (see
Deallocate()).
 
\return \c xlretSuccess or \c xlretInvXloper if no memory is could 
be allocated.
*/
int XlfOper::Allocate()
{
  lpxloper_ = (LPXLOPER)XlfExcel::Instance().GetMemory(sizeof(XLOPER));
  if (!lpxloper_)
    return xlretInvXloper;
  lpxloper_->xltype = xltypeNil;
  return xlretSuccess;
}

void XlfOper::FreeAuxiliaryMemory() const
{
  int err = XlfExcel::Instance().XlfExcel::Instance().Call(xlFree, NULL, 1, (LPXLOPER)lpxloper_);
  if (err != xlretSuccess)
    std::cerr << __HERE__ << "Call to xlFree failed" << std::endl;
  return;
}

/*!
\param type is an integer indicating the target type we want to coerce to.
\param result is the XLOPER where to store the output.
*/
int XlfOper::Coerce(short type, XlfOper& result) const
{
  XlfOper xlType(type);
  int xlret = XlfExcel::Instance().Call(xlCoerce, (LPXLOPER)result, 2, (LPXLOPER)lpxloper_, (LPXLOPER)xlType);
  return xlret;
}

/*!
Attempts to convert the implict object to a double. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOper::ConvertToDouble.
*/
double XlfOper::AsDouble(int * pxlret) const
{
  double d;
  int xlret = ConvertToDouble(d);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return d;
};
double XlfOper::AsDouble(const std::string& ErrorId, int * pxlret) const
{
  double d;
  int xlret = ConvertToDouble(d);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError( xlret,"Conversion to double "+ErrorId);
  return d;
};

int XlfOper::ConvertToDouble(double& d) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeInt)
  {
    d = lpxloper_->val.w;
    xlret=xlretSuccess;
  }
  else if (lpxloper_->xltype & xltypeNum)
  {
    d = lpxloper_->val.num;
    xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xltypeNum,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToDouble(d);
  }
  return xlret;
};

/*!
Attempts to convert the implict object to a an array.
Does this by calling AsDoubleVector.
If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

*/
MyArray XlfOper::AsArray(DoubleVectorConvPolicy policy, int * pxlret) const
{
	std::vector<double> tmp(AsDoubleVector(policy,pxlret));
	MyArray result(tmp.size());
	for (unsigned long i=0; i < result.size(); i++)
		result[i] = tmp[i];

	return result;
}

MyArray XlfOper::AsArray(const std::string& ErrorId,DoubleVectorConvPolicy policy, int * pxlret ) const
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
std::vector<double> XlfOper::AsDoubleVector(DoubleVectorConvPolicy policy, int * pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(v, policy);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return v;
}
std::vector<double> XlfOper::AsDoubleVector(const std::string& ErrorId, DoubleVectorConvPolicy policy, int * pxlret) const
{
  std::vector<double> v;
  int xlret = ConvertToDoubleVector(v, policy);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId+" conversion to double vector");
  return v;
}
/*!
Converts the data in the range in a vector of double according to the specified policy.
 
\pre All values in the range should be convertible to a double.
 
\return xlretFailed if the policy is UniDimensional and the range is not uni dimensional
and xlretSuccess otherwise or whatever error occurs during coercing the data to double.
 
\sa DoubleVectorConvPolicy
*/
int XlfOper::ConvertToDoubleVector(std::vector<double>& v, DoubleVectorConvPolicy policy) const
{
	if (lpxloper_->xltype == xltypeMissing)
    {
        v.resize(0);
        return xlretSuccess;
    }

	if (lpxloper_->xltype & xltypeNum)
	{
		// first test if double
		double d=0.0;
		int xlret1 = ConvertToDouble(d);

		if (xlret1 == xlretSuccess)
		{
			v.resize(1);
			v[0] = d;
			return xlret1;
		}
	}

  XlfRef ref;

  int xlret = ConvertToRef(ref);
  if (xlret != xlretSuccess)
    return xlret;

  size_t nbRows = ref.GetNbRows();
  size_t nbCols = ref.GetNbCols();

  bool isUniDimRange = ( nbRows == 1 || nbCols == 1 );
  if (policy == UniDimensional && ! isUniDimRange)
    // not a vector we return a failure
    return xlretFailed;

  size_t n = nbRows*nbCols;
  v.resize(n);

  for (size_t i = 0; i < nbRows; ++i)
  {
    for (size_t j = 0; j < nbCols; ++j)
    {
      if (policy == RowMajor)
        // C-like dense matrix storage
        xlret = ref(i,j).ConvertToDouble(v[i*nbCols+j]);
      else
        // Fortran-like dense matrix storage. Does not matter if the policy is UniDimensional
        xlret = ref(i,j).ConvertToDouble(v[j*nbRows+i]);
      if (xlret != xlretSuccess)
        return xlret;
    }
  }
  return xlret;
};

/*!
Attempts to convert the implict object to a short. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOper::ConvertToShort.
*/
short XlfOper::AsShort(int * pxlret) const
{
  short s;
  int xlret = ConvertToShort(s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

short XlfOper::AsShort(const std::string& ErrorId, int * pxlret) const
{
  short s;
  int xlret = ConvertToShort(s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId+" conversion to short failed");
  return s;
};
int XlfOper::ConvertToShort(short& s) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeNum)
  {
    s = static_cast<short>(lpxloper_->val.num);
    xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xltypeNum,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToShort(s);
  }
  return xlret;
};

/*!
Attempts to convert the implict object to a bool. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOper::ConvertToBool.
*/
bool XlfOper::AsBool(int * pxlret) const
{
  bool b;
  int xlret = ConvertToBool(b);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return b;
};
bool XlfOper::AsBool(const std::string& ErrorId, int * pxlret) const
{
  bool b;
  int xlret = ConvertToBool(b);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId+" conversion to bool failed");
  return b;
};
int XlfOper::ConvertToBool(bool& b) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeBool)
  {
    b = (lpxloper_->val.boolean != 0);
    xlret = xlretSuccess;
  }
  else
  {
    // see ConvertToDouble
    XLOPER tmp;
    XlfOper cast(&tmp);
    xlret = Coerce(xltypeBool,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToBool(b);
  }
  return xlret;
};

/*!
Attempts to convert the implict object to a matrix. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOper::ConvertToMatrix.
*/
MyMatrix XlfOper::AsMatrix( int * pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to matrix failed");
  return output;
}

MyMatrix XlfOper::AsMatrix( const std::string& ErrorId, int * pxlret) const
{
  MyMatrix output; // will be resized anyway
  int xlret = ConvertToMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId+" conversion to matrix failed");
  return output;
}
/*! converts the XlfOper to a matrix, since if its a valid matrix
its also a valid cellmatrix we convert to cell matrix first,
note this necessitates passing as a P not an R
*/
int XlfOper::ConvertToMatrix(MyMatrix& value) const
{
	CellMatrix tmp(1,1);// will be resized anyway
	int xlret = ConvertToCellMatrix(tmp);
	if (xlret != xlretSuccess)
		return xlret;

	value = MyMatrix(tmp.RowsInStructure(), tmp.ColumnsInStructure());
	for (unsigned long i =0; i < tmp.RowsInStructure(); i++)
		for (unsigned long j =0; j < tmp.ColumnsInStructure(); j++)
			if (tmp(i,j).IsANumber())
				ChangingElement(value,i,j) = tmp(i,j).NumericValue();
			else
				return xlretFailed;

	return xlretSuccess;
}

/*!
Attempts to convert the implict object to a cell matrix. If pxlret is 
not null the method won't throw and the Excel return code will be returned 
in this variable.

\sa XlfOper::ConvertToCellMatrix.
*/
CellMatrix XlfOper::AsCellMatrix( int * pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret," conversion to cell matrix failed");
  return output;
}

CellMatrix XlfOper::AsCellMatrix( const std::string& ErrorId, int * pxlret) const
{
  CellMatrix output(1,1); // will be resized anyway
  int xlret = ConvertToCellMatrix(output);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret,ErrorId+" conversion to cell matrix failed");
  return output;
}
int XlfOper::ConvertToCellMatrix(CellMatrix& output) const
{    
	XlfRef ref;

   
    if (lpxloper_->xltype == xltypeMissing || lpxloper_->xltype == xltypeNil )
    {
	
        CellMatrix tmp(1,1);
        output = tmp;
        
        return xlretSuccess;
    }
    
    if (lpxloper_->xltype == xltypeNum)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = lpxloper_->val.num;
        
        output = tmp;

 
        
        return xlretSuccess;
    }

	if (lpxloper_->xltype == xltypeBool)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = (lpxloper_->val.boolean >0);
        
        output = tmp;

        
        return xlretSuccess;
    }

	if (lpxloper_->xltype == xltypeErr)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = CellValue(lpxloper_->val.err,true);
        
        output = tmp;
        
        return xlretSuccess;
    }

    if (lpxloper_->xltype == xltypeStr)
    {
        CellMatrix tmpCell(1,1);
        
        unsigned long len = *((*lpxloper_).val.str);
        
        std::string tmp;
        tmp.resize(len);
        
        
        for(unsigned long k=0; k<len; ++k)
            tmp[k]= ((*lpxloper_).val.str)[k+1];
        
        
        tmpCell(0,0) = tmp;
        
        output = tmpCell;

        return xlretSuccess;
    }

    
    if (lpxloper_->xltype == xltypeMulti)
    {
        unsigned long rows = lpxloper_->val.array.rows;
        unsigned long columns = lpxloper_->val.array.columns;
        CellMatrix result(rows,columns);

        for (unsigned long i=0; i < rows; i++)
            for (unsigned long j=0; j < columns; j++)
            {
                unsigned long thisType = (*lpxloper_).val.array.lparray[i*columns+j].xltype;
                if (thisType == xltypeNum)
                {
                    double x = (*lpxloper_).val.array.lparray[i*columns+j].val.num;
                    result(i,j) = x;  
                }
                else
                {   
                    if (thisType==xltypeStr)
                    {
                          unsigned long len = *((*lpxloper_).val.array.lparray[i*columns+j].val.str);
  
                          std::string tmp;
                          tmp.resize(len);

                          for(unsigned long k=0; k<len; ++k)
                            tmp[k]=
                            ((*lpxloper_).val.array.lparray[i*columns+j].val.str)[k+1];
                        
                          result(i,j) = tmp;
                    }
                    
                    else     
						if (thisType == xltypeBool)
						{	
							result(i,j) = ((*lpxloper_).val.array.lparray[i*columns+j].val.boolean > 0);
						}
						else
							if (thisType== xltypeErr)
							{
								result(i,j) = CellValue(((*lpxloper_).val.array.lparray[i*columns+j].val.err),true);
							}
							else
		                        if (thisType!=xltypeMissing && thisType != xltypeNil)
			                        throw("cell contains neither number nor string nor boolean nor empty");
                }
                    
            }

        output= result;

        
        return xlretSuccess;


    }

    int xlret = ConvertToRef(ref);
    if (xlret != xlretSuccess)
        return xlret;
    
    unsigned long nbRows = ref.GetNbRows();
    unsigned long nbCols = ref.GetNbCols();
    
    output = CellMatrix(nbRows,nbCols);
	for (unsigned long i = 0; i < nbRows; ++i)
	{
		for (unsigned long j = 0; j < nbCols; ++j)
		{
			unsigned long type = ref(static_cast<WORD>(i),static_cast<BYTE>(j)).lpxloper_->xltype;

			if (type == xltypeRef)
			{
				XlfRef xlrefij;

				int xlretij = ref(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToRef(xlrefij);

				if (xlretij != xlretSuccess)
					return xlretij;

				type = ref(0UL,0UL).lpxloper_->xltype;

				if (type == xltypeNum)
				{
					double tmp;
					xlret = xlrefij(0UL,0UL).ConvertToDouble(tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else 
					if (type == xltypeErr)
					{
						WORD tmp;

						xlret = xlrefij(0UL,0UL).ConvertToErr(tmp);

						output(i,j) = CellValue(tmp,true);

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					if (type == xltypeBool)
					{
						bool tmp;

						xlret = xlrefij(0UL,0UL).ConvertToBool(tmp);

						output(i,j) = tmp;

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					{
						char* tmp;
						if (type == xltypeStr || type == xltypeSRef)
						{
							xlret = xlrefij(0UL,0UL).ConvertToString(tmp);
							output(i,j) = std::string(tmp);

							if (xlret != xlretSuccess)
								return xlret;
						} 
						else
						{

							if (type != xltypeMissing)
								return xlretInvXloper;

						}

					}




			}
			else 
				if (type == xltypeNum)
				{
					double tmp;
					xlret = ref(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToDouble(tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else
				{
					char* tmp;
					if (type == xltypeStr || type == xltypeSRef)
					{
						xlret = ref(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToString(tmp);
						output(i,j) = std::string(tmp);

						if (xlret != xlretSuccess)
							return xlret;
					} 
					else
					{
						if (ref(static_cast<WORD>(i),static_cast<BYTE>(j)).lpxloper_->xltype != xltypeMissing)
							return xlretInvXloper;

					}

				}
		}

	}  
	return xlret;

}

int XlfOper::ConvertToErr(WORD& e) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeErr)
  {
    e = lpxloper_->val.err ;
    xlret = xlretSuccess;
  }
  else
  {
    // see ConvertToDouble
    XLOPER tmp;
    XlfOper cast(&tmp);
    xlret = Coerce(xltypeErr,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToErr(e);
  }
  return xlret;
};

/*!
Attempts to convert the implict object to a char string. If pxlret is not 
null the method won't throw and the Excel return code will be returned in 
this variable.

\sa XlfOper::ConvertToString.

The XLL allocates the memory on its own buffer. This buffer is automatically 
freed when a function of the XLL is called again. Note that coerce to
a char string is the slowest cast of all.
*/
char * XlfOper::AsString(int * pxlret) const
{
  char * s;
  int xlret = ConvertToString(s);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return s;
};

char * XlfOper::AsString(const std::string& ErrorId, int * pxlret) const
{
  char * s;
  int xlret = ConvertToString(s);
  if (pxlret)
    *pxlret=xlret;
  else
	  ThrowOnError(xlret,ErrorId+" conversion to char* failed");
  return s;
};
int XlfOper::ConvertToString(char *& s) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeStr)
  {
    size_t n = lpxloper_->val.str[0];
    s = XlfExcel::Instance().GetMemory(n + 1);
    memcpy(s, lpxloper_->val.str + 1, n);
    s[n] = 0;
    xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER tmp;
    // Second argument true marks XlfOper so that xlFree is called on the
    // MS Excel allocated memory (the string) when XlfOper goes out of scope.
    XlfOper cast(&tmp);
    xlret = Coerce(xltypeStr,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToString(s);
  }
  return xlret;
}

/*!
Attempts to convert the implict object to an XlfRef. If pxlret is not null
the method won't throw and the Excel return code will be returned in this
variable.

\sa XlfOper::ConvertToRef.
*/
XlfRef XlfOper::AsRef(int * pxlret) const
{
  XlfRef r;
  int xlret = ConvertToRef(r);
  if (pxlret)
    *pxlret=xlret;
  else
    ThrowOnError(xlret);
  return r;
}

int XlfOper::ConvertToRef(XlfRef& r) const throw()
{
  int xlret;

  if (lpxloper_ == 0)
    return xlretInvXloper;

  if (lpxloper_->xltype & xltypeRef)
  {
    const XLREF& ref=lpxloper_->val.mref.lpmref->reftbl[0];
    r = XlfRef (ref.rwFirst,  // top
                ref.colFirst, // left
                ref.rwLast,   // bottom
                ref.colLast,  // right
                lpxloper_->val.mref.idSheet); // sheet id
    xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER tmp;
    // Second argument true marks XlfOper so that xlFree is called on the
    // MS Excel allocated memory (the reference array) when XlfOper goes
    // out of scope.
    XlfOper cast(&tmp);
    xlret = Coerce(xltypeRef,cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToRef(r);
  }
  return xlret;
}

XlfOper& XlfOper::Set(const MyMatrix& values)
{
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
		return Set(CellMatrix(1,1));
	}
	CellMatrix tmp(static_cast<unsigned long>(values.size()), 1UL);
	for (unsigned long i=0; i < values.size(); i++)
			tmp(i,0) = values[i];
	return Set(tmp);
}

XlfOper& XlfOper::Set(const CellMatrix& cells)
{
    int r= cells.RowsInStructure();
    int c= cells.ColumnsInStructure();

	c= c<  255 ? c :255;


    lpxloper_->xltype = xltypeMulti;
    lpxloper_->val.array.rows = r;
    lpxloper_->val.array.columns = c; 

    lpxloper_->val.array.lparray 
            = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));

    for (int i=0; i < r; i++)
        for (int j=0; j < c; j++)
        {
            int k = i*c +j;
            if (cells(i,j).IsANumber())
                lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).NumericValue());
            else
                if (cells(i,j).IsAString())
                    lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).StringValue().c_str());
                else
					if (cells(i,j).IsBoolean())
						    lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).BooleanValue());
					else
						if (cells(i,j).IsError())
							 lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper(static_cast<WORD>(cells(i,j).ErrorValue()),true);
						else               
					            lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper("");
        }

    return *this;


}

XlfOper& XlfOper::Set(LPXLOPER lpxloper)
{
  assert(lpxloper != 0);
  lpxloper_ = lpxloper;
  return *this;
}

XlfOper& XlfOper::Set(double value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeNum;
    lpxloper_->val.num = value;
  }
  return *this;
}

XlfOper& XlfOper::Set(short value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeInt;
    lpxloper_->val.w = value;
  }
  return *this;
}

//! bool for disambiguation
XlfOper& XlfOper::Set(short value, bool Error)
{
  if (lpxloper_)
  {
	if (Error)
	{
		lpxloper_->xltype = xltypeErr;
		lpxloper_->val.err =value;
	}
	else
	{
		lpxloper_->xltype = xltypeInt;
		lpxloper_->val.w = value;
	}
  }
  return *this;
}

XlfOper& XlfOper::Set(bool value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeBool;
    lpxloper_->val.boolean = value;
  }
  return *this;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the XlfRef is not copied.
*/
XlfOper& XlfOper::Set(const XlfRef& range)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeRef;
    XLMREF * pmRef = reinterpret_cast<XLMREF *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF)));
    // if no memory is available
    if (pmRef == 0)
    {
      // set XlfOper to an invalid state
      lpxloper_=0;
    }
    else
    {
      pmRef->count=1;
      pmRef->reftbl[0].rwFirst = range.GetRowBegin();
      pmRef->reftbl[0].rwLast = range.GetRowEnd()-1;
      pmRef->reftbl[0].colFirst = range.GetColBegin();
      pmRef->reftbl[0].colLast = range.GetColEnd()-1;
      lpxloper_->val.mref.lpmref = pmRef;
      lpxloper_->val.mref.idSheet = range.GetSheetId();
    }
  }
  return *this;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the string is not copied.
 
\note String longer than 255 characters are truncated. A warning
is issued in debug mode.
*/
XlfOper& XlfOper::Set(const char *value)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeStr;
    int n = static_cast<unsigned int>(strlen(value));
    if (n >= 256)
      std::cerr << __HERE__ << "String too long is truncated" << std::endl;
    // One byte more for NULL terminal char (allow use of strcpy)
    // and one for the std::string size (convention used by Excel)
    LPSTR str = reinterpret_cast<LPSTR>(XlfExcel::Instance().GetMemory(n + 2));
    if (str == 0)
    {
      lpxloper_=0;
    }
    else
    {
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif
      strcpy(str + 1, value);
      // the number of character include the final \0 or not ?
      lpxloper_->val.str = str;
      lpxloper_->val.str[0] = (BYTE)(n + 1);
    }
  }
  return *this;
}

/*!
\sa XlfOper::Error(WORD)
*/
XlfOper& XlfOper::SetError(WORD error)
{
  if (lpxloper_)
  {
    lpxloper_->xltype = xltypeErr;
    lpxloper_->val.err = error;
  }
  return *this;
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
    throw std::runtime_error("invalid number of argument");
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
    throw XlfException("invalid OPER structure (memory could be exhausted),"+Identifier);
  if (xlret & xlretFailed)
    throw std::runtime_error("command failed, "+Identifier);
  if (xlret & xlretInvCount)
    throw std::runtime_error("invalid number of argument, "+Identifier);
  if (xlret & xlretInvXlfn)
    throw std::runtime_error("invalid function number, "+Identifier);
  // should never get there.
  assert(0);
  return xlret;
}

