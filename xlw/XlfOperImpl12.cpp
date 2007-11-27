
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

/*!
\file XlfOperImpl12.cpp
\brief Implements the XlfOperImpl12 class.
*/

// $Id: XlfOper.cpp 335 2007-06-25 03:47:43Z markjoshi $

#include <xlw/XlfOperImpl12.h>
#include <xlw/XlfOper.h>
#include <xlw/XlfException.h>
#include <xlw/macros.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

const XlfOperImpl12 &XlfOperImpl12::instance() {
    if (instance_) {
        XlfOperImpl12 *ret = dynamic_cast<XlfOperImpl12*>(instance_);
        if (ret) return *ret;
    }        
    throw("Attempt to reference uninitialized XlfOperImpl12 object");
}

/*!
Calls Deallocate() to free the XLOPER allocated by the XLL. XLOPER allocated
by Excel remain under Excel responsibility.
 
Calls FreeAuxiliaryMemory if the XLOPER is marked by XlfOper::Call as an 
XLOPER returned by MS Excel and if the type matches one of xltypeStr, 
xltypeRef, xltypeMulti, xltypeBigData.
*/
void XlfOperImpl12::destroy(const XlfOperUnion &xlfOperUnion) const
{
  if (!xlfOperUnion.lpxloper12)
    return;

  int type = xlfOperUnion.lpxloper12->xltype;

//  Only the types below can be flagged xlFreeAuxMem, thus the test is 
//  actually redundant: we don't need to re-check the type of the oper.
//  
//  bool canHaveAuxMem = (type & xltypeStr ||
//                        type & xltypeRef ||
//                        type & xltypeMulti ||
//                        type & xltypeBigData);
  if (type & XlfOperImpl::xlbitFreeAuxMem)
  {
    // switch back the bit as it was originally
    xlfOperUnion.lpxloper12->xltype &= ~XlfOperImpl::xlbitFreeAuxMem;
    FreeAuxiliaryMemory(xlfOperUnion);
  }
  return;
}

/*!
Allocates 32 bytes (size of an XLOPER12) on the temporary buffer
stored by XlfExcel with a call to XlfExcel::GetMemory().
 
\warning Each XlfOper allocation causes a call to Allocate which in turn
reserves the necessary number of bytes in the internal buffer. The
problem is that even temporary XlfOper used inside the xll function uses
this internal buffer. This buffer is not freed before the next call to
the xll to ensure Excel can use the data before they are freed. This
causes a bottleneck if the function uses many temporary XlfOper (see
Deallocate()).
 
\return \c xlretSuccess or \c xlretInvXloper if no memory could 
be allocated.
*/
int XlfOperImpl12::Allocate(XlfOperUnion &xlfOperUnion) const
{
  xlfOperUnion.lpxloper12 = (LPXLOPER12)XlfExcel::Instance().GetMemory(sizeof(XLOPER12));
  if (!xlfOperUnion.lpxloper12)
    return xlretInvXloper;
  xlfOperUnion.lpxloper12->xltype = xltypeNil;
  return xlretSuccess;
}

void XlfOperImpl12::FreeAuxiliaryMemory(const XlfOperUnion &xlfOperUnion) const
{
  //int err = XlfExcel::Instance().XlfExcel::Instance().Call12(xlFree, NULL, 1, xlfOperUnion.lpxloper12);
  //if (err != xlretSuccess)
  //  std::cerr << XLW__HERE__ << "Call to xlFree failed" << std::endl;
  return;
}

/*!
\param type is an integer indicating the target type we want to coerce to.
\param result is the XLOPER where to store the output.
*/
int XlfOperImpl12::Coerce(const XlfOperUnion &xlfOperUnion, short type, XlfOperUnion &result) const
{
  XlfOper xlType(type);
  int xlret = XlfExcel::Instance().Call12(xlCoerce, result.lpxloper12, 2, xlfOperUnion.lpxloper12, xlType.xlfOperUnion_.lpxloper12);
  return xlret;
}

int XlfOperImpl12::ConvertToDouble(const XlfOperUnion &xlfOperUnion, double& d) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeInt)
  {
    d = xlfOperUnion.lpxloper12->val.w;
    xlret=xlretSuccess;
  }
  else if (xlfOperUnion.lpxloper12->xltype & xltypeNum)
  {
    d = xlfOperUnion.lpxloper12->val.num;
    xlret=xlretSuccess;
  }
  else
  {    
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xlfOperUnion, xltypeNum, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToDouble(cast.xlfOperUnion_, d);
  }
  return xlret;
};

/*!
Converts the data in the range in a vector of double according to the specified policy.
 
\pre All values in the range should be convertible to a double.
 
\return xlretFailed if the policy is UniDimensional and the range is not uni dimensional
and xlretSuccess otherwise or whatever error occurs during coercing the data to double.
 
\sa DoubleVectorConvPolicy
*/
int XlfOperImpl12::ConvertToDoubleVector(const XlfOperUnion &xlfOperUnion, std::vector<double>& v, DoubleVectorConvPolicy policy) const
{
	if (xlfOperUnion.lpxloper12->xltype == xltypeMissing)
    {
        v.resize(0);
        return xlretSuccess;
    }

	if (xlfOperUnion.lpxloper12->xltype & xltypeNum)
	{
		// first test if double
		double d=0.0;
		int xlret1 = ConvertToDouble(xlfOperUnion, d);

		if (xlret1 == xlretSuccess)
		{
			v.resize(1);
			v[0] = d;
			return xlret1;
		}
	}

  XlfRef ref;

  int xlret = ConvertToRef(xlfOperUnion, ref);
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
        xlret = ConvertToDouble(ref(i,j).xlfOperUnion_, v[i*nbCols+j]);
      else
        // Fortran-like dense matrix storage. Does not matter if the policy is UniDimensional
        xlret = ConvertToDouble(ref(i,j).xlfOperUnion_, v[j*nbRows+i]);
      if (xlret != xlretSuccess)
        return xlret;
    }
  }
  return xlret;
};

int XlfOperImpl12::ConvertToShort(const XlfOperUnion &xlfOperUnion, short& s) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeNum)
  {
    s = static_cast<short>(xlfOperUnion.lpxloper12->val.num);
    xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xlfOperUnion, xltypeNum, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToShort(cast.xlfOperUnion_, s);
  }
  return xlret;
};

int XlfOperImpl12::ConvertToBool(const XlfOperUnion &xlfOperUnion, bool& b) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeBool)
  {
    b = (xlfOperUnion.lpxloper12->val.xbool != 0);
    xlret = xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOperUnion, xltypeBool, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToBool(cast.xlfOperUnion_, b);
  }
  return xlret;
};

/*! Converts the XlfOper to a matrix, since if it's a valid matrix
it's also a valid cellmatrix we convert to cell matrix first,
note this necessitates passing as a P not an R
*/
int XlfOperImpl12::ConvertToMatrix(const XlfOperUnion &xlfOperUnion, MyMatrix& value) const
{
	// deal with empty case first
	if (xlfOperUnion.lpxloper12->xltype == xltypeMissing || xlfOperUnion.lpxloper12->xltype == xltypeNil )
    {
	
       MyMatrix tmp;
       value = tmp;
        
        return xlretSuccess;
    }

	CellMatrix tmp(1,1);// will be resized anyway
	int xlret = ConvertToCellMatrix(xlfOperUnion, tmp);
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

int XlfOperImpl12::ConvertToCellMatrix(const XlfOperUnion &xlfOperUnion, CellMatrix& output) const
{    
	XlfRef ref;

   
    if (xlfOperUnion.lpxloper12->xltype == xltypeMissing || xlfOperUnion.lpxloper12->xltype == xltypeNil)
    {
	
        CellMatrix tmp(1,1);
        output = tmp;
        
        return xlretSuccess;
    }
    
    if (xlfOperUnion.lpxloper12->xltype == xltypeNum)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = xlfOperUnion.lpxloper12->val.num;
        
        output = tmp;

        return xlretSuccess;
    }

	if (xlfOperUnion.lpxloper12->xltype == xltypeBool)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = (xlfOperUnion.lpxloper12->val.xbool >0);
        
        output = tmp;

        return xlretSuccess;
    }

	if (xlfOperUnion.lpxloper12->xltype == xltypeErr)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = CellValue(xlfOperUnion.lpxloper12->val.err, true);
        
        output = tmp;
        
        return xlretSuccess;
    }

    if (xlfOperUnion.lpxloper12->xltype == xltypeStr)
    {
        CellMatrix tmpCell(1,1);
        
        unsigned long len = *((*xlfOperUnion.lpxloper12).val.str);
        
        std::string tmp;
        tmp.resize(len);
        
        for(unsigned long k=0; k<len; ++k)
            tmp[k]= ((*xlfOperUnion.lpxloper12).val.str)[k+1];
        
        tmpCell(0,0) = tmp;
        
        output = tmpCell;

        return xlretSuccess;
    }

    if (xlfOperUnion.lpxloper12->xltype == xltypeMulti)
    {
        unsigned long rows = xlfOperUnion.lpxloper12->val.array.rows;
        unsigned long columns = xlfOperUnion.lpxloper12->val.array.columns;
        CellMatrix result(rows,columns);

        for (unsigned long i=0; i < rows; i++)
            for (unsigned long j=0; j < columns; j++)
            {
                unsigned long thisType = (*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].xltype;
                if (thisType == xltypeNum)
                {
                    double x = (*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].val.num;
                    result(i,j) = x;  
                }
                else
                {   
                    if (thisType==xltypeStr)
                    {
                          unsigned long len = *((*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].val.str);
  
                          std::wstring tmp;
                          tmp.resize(len);

                          for(unsigned long k=0; k<len; ++k)
                            tmp[k]=
                            ((*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].val.str)[k+1];
                        
                          result(i,j) = tmp;
                    }
                    
                    else     
						if (thisType == xltypeBool)
						{	
							result(i,j) = ((*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].val.xbool > 0);
						}
						else
							if (thisType== xltypeErr)
							{
								result(i,j) = CellValue(((*xlfOperUnion.lpxloper12).val.array.lparray[i*columns+j].val.err),true);
							}
							else
		                        if (thisType!=xltypeMissing && thisType != xltypeNil)
			                        throw("cell contains neither number nor string nor boolean nor empty");
                }
                    
            }

        output= result;

        return xlretSuccess;

    }

    int xlret = ConvertToRef(xlfOperUnion, ref);
    if (xlret != xlretSuccess)
        return xlret;
    
    unsigned long nbRows = ref.GetNbRows();
    unsigned long nbCols = ref.GetNbCols();
    
    output = CellMatrix(nbRows,nbCols);
	for (unsigned long i = 0; i < nbRows; ++i)
	{
		for (unsigned long j = 0; j < nbCols; ++j)
		{
			unsigned long type = ref(static_cast<WORD>(i),static_cast<BYTE>(j)).xlfOperUnion_.lpxloper12->xltype;

			if (type == xltypeRef)
			{
				XlfRef xlrefij;

				int xlretij = ConvertToRef(ref(static_cast<WORD>(i),static_cast<BYTE>(j)).xlfOperUnion_, xlrefij);

				if (xlretij != xlretSuccess)
					return xlretij;

				type = ref(0UL,0UL).xlfOperUnion_.lpxloper12->xltype;

				if (type == xltypeNum)
				{
					double tmp;
					xlret = ConvertToDouble(xlrefij(0UL,0UL).xlfOperUnion_, tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else 
					if (type == xltypeErr)
					{
						WORD tmp;

						xlret = ConvertToErr(xlrefij(0UL,0UL).xlfOperUnion_, tmp);

						output(i,j) = CellValue(tmp,true);

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					if (type == xltypeBool)
					{
						bool tmp;

						xlret = ConvertToBool(xlrefij(0UL,0UL).xlfOperUnion_, tmp);

						output(i,j) = tmp;

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					{
						char* tmp;
						if (type == xltypeStr || type == xltypeSRef)
						{
							xlret = ConvertToString(xlrefij(0UL,0UL).xlfOperUnion_, tmp);
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
					xlret = ConvertToDouble(ref(static_cast<WORD>(i),static_cast<BYTE>(j)).xlfOperUnion_, tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else
				{
					char* tmp;
					if (type == xltypeStr || type == xltypeSRef)
					{
						xlret = ConvertToString(ref(static_cast<WORD>(i),static_cast<BYTE>(j)).xlfOperUnion_, tmp);
						output(i,j) = std::string(tmp);

						if (xlret != xlretSuccess)
							return xlret;
					} 
					else
					{
						if (ref(static_cast<WORD>(i),static_cast<BYTE>(j)).xlfOperUnion_.lpxloper12->xltype != xltypeMissing)
							return xlretInvXloper;

					}

				}
		}

	}  
	return xlret;

}

int XlfOperImpl12::ConvertToErr(const XlfOperUnion &xlfOperUnion, WORD& e) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeErr)
  {
    e = xlfOperUnion.lpxloper12->val.err ;
    xlret = xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOperUnion, xltypeErr, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToErr(cast.xlfOperUnion_, e);
  }
  return xlret;
};

int XlfOperImpl12::ConvertToString(const XlfOperUnion &xlfOperUnion, char *& s) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeStr)
  {
    BYTE nB = xlfOperUnion.lpxloper12->val.str[0]; // to make numbers bigger than 128 behave properly
    size_t n = static_cast<size_t>(nB);
    s = XlfExcel::Instance().GetMemory(n + 1);
    wcstombs(s, xlfOperUnion.lpxloper12->val.str + 1, n);
    s[n] = 0;
    xlret = xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOperUnion, xltypeStr, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToString(cast.xlfOperUnion_, s);
  }
  return xlret;
}

int XlfOperImpl12::ConvertToRef(const XlfOperUnion &xlfOperUnion, XlfRef& r) const throw()
{
  int xlret;

  if (xlfOperUnion.lpxloper12 == 0)
    return xlretInvXloper;

  if (xlfOperUnion.lpxloper12->xltype & xltypeRef)
  {
    const XLREF12& ref=xlfOperUnion.lpxloper12->val.mref.lpmref->reftbl[0];
    r = XlfRef (ref.rwFirst,  // top
                ref.colFirst, // left
                ref.rwLast,   // bottom
                ref.colLast,  // right
                xlfOperUnion.lpxloper12->val.mref.idSheet); // sheet id
    xlret = xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOperUnion, xltypeRef, cast.xlfOperUnion_);
    if (xlret == xlretSuccess)
      xlret = ConvertToRef(cast.xlfOperUnion_, r);
  }
  return xlret;
}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, const CellMatrix& cells) const
{
    int r = cells.RowsInStructure();
    int c = cells.ColumnsInStructure();

	c = c < 255 ? c : 255;

    xlfOperUnion.lpxloper12->xltype = xltypeMulti;
    xlfOperUnion.lpxloper12->val.array.rows = r;
    xlfOperUnion.lpxloper12->val.array.columns = c; 

    xlfOperUnion.lpxloper12->val.array.lparray 
            = (LPXLOPER12)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER12));

    for (int i=0; i < r; i++)
        for (int j=0; j < c; j++)
        {
            int k = i*c +j;
            if (cells(i,j).IsANumber())
                xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).NumericValue());
            else
                if (cells(i,j).IsAString())
                    xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).StringValue());
                else
                if (cells(i,j).IsAWstring())
                    xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).WstringValue());
                else
					if (cells(i,j).IsBoolean())
						    xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).BooleanValue());
					else
						if (cells(i,j).IsError())
							 xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper(static_cast<WORD>(cells(i,j).ErrorValue()),true);
						else               
					            xlfOperUnion.lpxloper12->val.array.lparray[k] = *(LPXLOPER12)XlfOper("");
        }

}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, LPXLFOPER lpxlfoper) const
{
  assert(lpxlfoper != 0);
  xlfOperUnion.lpxloper12 = reinterpret_cast<LPXLOPER12>(lpxlfoper);
}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, double value) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeNum;
    xlfOperUnion.lpxloper12->val.num = value;
  }
}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, short value) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeInt;
    xlfOperUnion.lpxloper12->val.w = value;
  }
}

//! bool for disambiguation
void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, short value, bool Error) const
{
  if (xlfOperUnion.lpxloper12)
  {
	if (Error)
	{
		xlfOperUnion.lpxloper12->xltype = xltypeErr;
		xlfOperUnion.lpxloper12->val.err =value;
	}
	else
	{
		xlfOperUnion.lpxloper12->xltype = xltypeInt;
		xlfOperUnion.lpxloper12->val.w = value;
	}
  }
}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, bool value) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeBool;
    xlfOperUnion.lpxloper12->val.xbool = value;
  }
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the XlfRef is not copied.
*/
void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, const XlfRef& range) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeRef;
    XLMREF12 * pmRef = reinterpret_cast<XLMREF12 *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF12)));
    // if no memory is available
    if (pmRef == 0)
    {
      // set XlfOper to an invalid state
      xlfOperUnion.lpxloper12=0;
    }
    else
    {
      pmRef->count=1;
      pmRef->reftbl[0].rwFirst = range.GetRowBegin();
      pmRef->reftbl[0].rwLast = range.GetRowEnd()-1;
      pmRef->reftbl[0].colFirst = range.GetColBegin();
      pmRef->reftbl[0].colLast = range.GetColEnd()-1;
      xlfOperUnion.lpxloper12->val.mref.lpmref = pmRef;
      xlfOperUnion.lpxloper12->val.mref.idSheet = range.GetSheetId();
    }
  }
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the string is not copied.
*/
void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, const char *value) const
{
  if (xlfOperUnion.lpxloper12)
  {
    int len = strlen(value);
    xlfOperUnion.lpxloper12->val.str = (XCHAR*)XlfExcel::Instance().GetMemory((len+1)*2);
    if (xlfOperUnion.lpxloper12->val.str) {
        xlfOperUnion.lpxloper12->xltype = xltypeStr;
        mbstowcs(xlfOperUnion.lpxloper12->val.str + 1, value, len);
        xlfOperUnion.lpxloper12->val.str[0] = len;
    } else {
        xlfOperUnion.lpxloper12 = 0;
    }
  }
}

void XlfOperImpl12::Set(XlfOperUnion &xlfOperUnion, const std::wstring &value) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeStr;
    xlfOperUnion.lpxloper12->val.str = (XCHAR*)XlfExcel::Instance().GetMemory((value.length()+1)*2);
    wcsncpy(xlfOperUnion.lpxloper12->val.str + 1, value.c_str(), value.length());
    xlfOperUnion.lpxloper12->val.str[0] = (BYTE)value.length();
  }
}

/*!
\sa XlfOper::Error(WORD)
*/
void XlfOperImpl12::SetError(XlfOperUnion &xlfOperUnion, WORD error) const
{
  if (xlfOperUnion.lpxloper12)
  {
    xlfOperUnion.lpxloper12->xltype = xltypeErr;
    xlfOperUnion.lpxloper12->val.err = error;
  }
}

XlfOper& XlfOperImpl12::assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const
{
  //if (xlfOper != &rhs) FIXME
    xlfOper.xlfOperUnion_.lpxloper12 = rhs.xlfOperUnion_.lpxloper12;
  return xlfOper;
}

LPXLOPER XlfOperImpl12::operator_LPXLOPER(const XlfOperUnion &xlfOperUnion) const
{
  throw("Unable to convert Excel 12 datatype to Excel 4 datatype - operation not yet implemented");
}

LPXLOPER12 XlfOperImpl12::operator_LPXLOPER12(const XlfOperUnion &xlfOperUnion) const
{
  return xlfOperUnion.lpxloper12;
}

LPXLFOPER XlfOperImpl12::operator_LPXLFOPER(const XlfOperUnion &xlfOperUnion) const
{
  return xlfOperUnion.lpxloper12;
}

bool XlfOperImpl12::IsMissing(const XlfOperUnion &xlfOperUnion) const
{
  return xlfOperUnion.lpxloper12->xltype == xltypeMissing;
}

bool XlfOperImpl12::IsError(const XlfOperUnion &xlfOperUnion) const
{
  return xlfOperUnion.lpxloper12->xltype == xltypeErr;
}

LPXLFOPER XlfOperImpl12::GetLPXLFOPER(const XlfOperUnion &xlfOperUnion) const
{
  return xlfOperUnion.lpxloper12;
}
