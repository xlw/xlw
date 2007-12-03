
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
#include <xlw/XlfRef.h>
#include <xlw/defines.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <xlw/CellMatrix.h>
#include <algorithm>

// Stop header precompilation
#ifdef _MSC_VER
#pragma hdrstop
#endif

/*!
Calls Deallocate() to free the XLOPER allocated by the XLL. XLOPER allocated
by Excel remain under Excel responsibility.
 
Calls FreeAuxiliaryMemory if the XLOPER is marked by XlfOper::Call as an 
XLOPER returned by MS Excel and if the type matches one of xltypeStr, 
xltypeRef, xltypeMulti, xltypeBigData.
*/
void XlfOperImpl12::destroy(const XlfOper &xlfOper) const
{
  if (!xlfOper.lpxloper12_)
    return;

  int type = xlfOper.lpxloper12_->xltype;

//  Only the types below can be flagged xlFreeAuxMem, thus the test is 
//  actually redundant: we don't need to re-check the type of the oper.
//  
//  bool canHaveAuxMem = (type & xltypeStr ||
//                        type & xltypeRef ||
//                        type & xltypeMulti ||
//                        type & xltypeBigData);
  if (type & XlfOper::xlbitFreeAuxMem)
  {
    // switch back the bit as it was originally
    xlfOper.lpxloper12_->xltype &= ~XlfOper::xlbitFreeAuxMem;
    FreeAuxiliaryMemory(xlfOper);
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
int XlfOperImpl12::Allocate(XlfOper &xlfOper) const
{
  xlfOper.lpxloper12_ = (LPXLOPER12)XlfExcel::Instance().GetMemory(sizeof(XLOPER12));
  if (!xlfOper.lpxloper12_)
    return xlretInvXloper;
  xlfOper.lpxloper12_->xltype = xltypeNil;
  return xlretSuccess;
}

void XlfOperImpl12::FreeAuxiliaryMemory(const XlfOper &xlfOper) const
{
  int err = XlfExcel::Instance().XlfExcel::Instance().Call(xlFree, NULL, 1, (LPXLFOPER)xlfOper.lpxloper12_);
  if (err != xlretSuccess)
    std::cerr << XLW__HERE__ << "Call to xlFree failed" << std::endl;
  return;
}

/*!
\param type is an integer indicating the target type we want to coerce to.
\param result is the XLOPER where to store the output.
*/
int XlfOperImpl12::Coerce(const XlfOper &xlfOper, short type, XlfOper& result) const
{
  XlfOper xlType(type);
  int xlret = XlfExcel::Instance().Call(xlCoerce, (LPXLFOPER)result, 2, (LPXLFOPER)xlfOper.lpxloper12_, (LPXLFOPER)xlType);
  return xlret;
}

int XlfOperImpl12::ConvertToDouble(const XlfOper &xlfOper, double& d) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeInt)
  {
    d = xlfOper.lpxloper12_->val.w;
    xlret=xlretSuccess;
  }
  else if (xlfOper.lpxloper12_->xltype & xltypeNum)
  {
    d = xlfOper.lpxloper12_->val.num;
    xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xlfOper, xltypeNum, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToDouble(d);
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
int XlfOperImpl12::ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& v, DoubleVectorConvPolicy policy) const
{
	if (xlfOper.lpxloper12_->xltype == xltypeMissing)
    {
        v.resize(0);
        return xlretSuccess;
    }

	if (xlfOper.lpxloper12_->xltype & xltypeNum)
	{
		// first test if double
		double d=0.0;
		int xlret1 = ConvertToDouble(xlfOper, d);

		if (xlret1 == xlretSuccess)
		{
			v.resize(1);
			v[0] = d;
			return xlret1;
		}
	}

	if (xlfOper.lpxloper12_->xltype & xltypeMulti)
	{
        size_t nbRows = xlfOper.lpxloper12_->val.array.rows;
        size_t nbCols = xlfOper.lpxloper12_->val.array.columns;

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
                size_t index;
                if (policy == RowMajor)
                    // C-like dense matrix storage
                    index = i*nbCols+j;
                else
                    // Fortran-like dense matrix storage. Does not matter if the policy is UniDimensional
                    index = j*nbRows+i;

                unsigned long thisType = (*xlfOper.lpxloper12_).val.array.lparray[i*nbCols+j].xltype;
                if (thisType == xltypeNum)
                {
                    v[index] = (*xlfOper.lpxloper12_).val.array.lparray[i*nbCols+j].val.num;
                }
                else
                {
                    int xlret =  XlfOper(&(*xlfOper.lpxloper12_).val.array.lparray[i*nbCols+j]).ConvertToDouble(v[index]);
                    if (xlret != xlretSuccess)
                        return xlret;
                }
            }
        }
        return xlretSuccess;
	}

  XlfRef ref;

  int xlret = ConvertToRef(xlfOper, ref);
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
        xlret = ref.element<XlfOper>(i,j).ConvertToDouble(v[i*nbCols+j]);
      else
        // Fortran-like dense matrix storage. Does not matter if the policy is UniDimensional
        xlret = ref.element<XlfOper>(i,j).ConvertToDouble(v[j*nbRows+i]);
      if (xlret != xlretSuccess)
        return xlret;
    }
  }
  return xlret;
};

int XlfOperImpl12::ConvertToShort(const XlfOper &xlfOper, short& s) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeNum)
  {
    s = static_cast<short>(xlfOper.lpxloper12_->val.num);
    xlret=xlretSuccess;
  }
  else
  {
    // Allocates tmp on the stack to avoid filling the internal buffer.
    XLOPER12 tmp;
    // Creates a XlfOper based on tmp.
    XlfOper cast(&tmp);
    // Coerces to numeric type.
    xlret = Coerce(xlfOper, xltypeNum, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToShort(s);
  }
  return xlret;
};

int XlfOperImpl12::ConvertToBool(const XlfOper &xlfOper, bool& b) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeBool)
  {
    b = (xlfOper.lpxloper12_->val.xbool != 0);
    xlret = xlretSuccess;
  }
  else
  {
    // see ConvertToDouble
    XLOPER12 tmp;
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOper, xltypeBool, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToBool(b);
  }
  return xlret;
};

/*! Converts the XlfOper to a matrix, since if it's a valid matrix
it's also a valid cellmatrix we convert to cell matrix first,
note this necessitates passing as a P not an R
*/
int XlfOperImpl12::ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& value) const
{
	// deal with empty case first
	if (xlfOper.lpxloper12_->xltype == xltypeMissing || xlfOper.lpxloper12_->xltype == xltypeNil )
    {
	
       MyMatrix tmp;
       value = tmp;
        
        return xlretSuccess;
    }

	CellMatrix tmp(1,1);// will be resized anyway
	int xlret = ConvertToCellMatrix(xlfOper, tmp);
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

int XlfOperImpl12::ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const
{    
	XlfRef ref;

   
    if (xlfOper.lpxloper12_->xltype == xltypeMissing || xlfOper.lpxloper12_->xltype == xltypeNil)
    {
	
        CellMatrix tmp(1,1);
        output = tmp;
        
        return xlretSuccess;
    }
    
    if (xlfOper.lpxloper12_->xltype == xltypeNum)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = xlfOper.lpxloper12_->val.num;
        
        output = tmp;

        return xlretSuccess;
    }

	if (xlfOper.lpxloper12_->xltype == xltypeBool)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = (xlfOper.lpxloper12_->val.xbool >0);
        
        output = tmp;

        return xlretSuccess;
    }

	if (xlfOper.lpxloper12_->xltype == xltypeErr)
    {
        CellMatrix tmp(1,1);
        
        tmp(0,0) = CellValue(xlfOper.lpxloper12_->val.err, true);
        
        output = tmp;
        
        return xlretSuccess;
    }

    if (xlfOper.lpxloper12_->xltype == xltypeStr)
    {
        CellMatrix tmpCell(1,1);
        
        unsigned long len = *((*xlfOper.lpxloper12_).val.str);
        
        std::string tmp;
        tmp.resize(len);
        
        for(unsigned long k=0; k<len; ++k)
            tmp[k]= ((*xlfOper.lpxloper12_).val.str)[k+1];
        
        tmpCell(0,0) = tmp;
        
        output = tmpCell;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper12_->xltype == xltypeMulti)
    {
        unsigned long rows = xlfOper.lpxloper12_->val.array.rows;
        unsigned long columns = xlfOper.lpxloper12_->val.array.columns;
        CellMatrix result(rows,columns);

        for (unsigned long i=0; i < rows; i++)
            for (unsigned long j=0; j < columns; j++)
            {
                unsigned long thisType = (*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].xltype;
                if (thisType == xltypeNum)
                {
                    double x = (*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].val.num;
                    result(i,j) = x;  
                }
                else
                {   
                    if (thisType==xltypeStr)
                    {
                          unsigned long len = *((*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].val.str);
  
                          std::wstring tmp;
                          tmp.resize(len);

                          for(unsigned long k=0; k<len; ++k)
                            tmp[k]=
                            ((*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].val.str)[k+1];
                        
                          result(i,j) = tmp;
                    }
                    
                    else     
						if (thisType == xltypeBool)
						{	
							result(i,j) = ((*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].val.xbool > 0);
						}
						else
							if (thisType== xltypeErr)
							{
								result(i,j) = CellValue(((*xlfOper.lpxloper12_).val.array.lparray[i*columns+j].val.err),true);
							}
							else
		                        if (thisType!=xltypeMissing && thisType != xltypeNil)
			                        throw("cell contains neither number nor string nor boolean nor empty");
                }
                    
            }

        output= result;

        return xlretSuccess;

    }

    int xlret = ConvertToRef(xlfOper, ref);
    if (xlret != xlretSuccess)
        return xlret;
    
    unsigned long nbRows = ref.GetNbRows();
    unsigned long nbCols = ref.GetNbCols();
    
    output = CellMatrix(nbRows,nbCols);
	for (unsigned long i = 0; i < nbRows; ++i)
	{
		for (unsigned long j = 0; j < nbCols; ++j)
		{
			unsigned long type = ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j)).lpxloper12_->xltype;

			if (type == xltypeRef)
			{
				XlfRef xlrefij;

                int xlretij = ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToRef(xlrefij);

				if (xlretij != xlretSuccess)
					return xlretij;


                // FIXME possible bug?  This line calls XlfOper::element(), which constructs an Xloper from an XlfRef.
                // The result returned to variable "type" is always xltypeRef and that value is not catered for below.
				type = ref.element<XlfOper>(0UL,0UL).lpxloper12_->xltype;

				if (type == xltypeNum)
				{
					double tmp;
					xlret = xlrefij.element<XlfOper>(0UL,0UL).ConvertToDouble(tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else 
					if (type == xltypeErr)
					{
						WORD tmp;

						xlret = xlrefij.element<XlfOper>(0UL,0UL).ConvertToErr(tmp);

						output(i,j) = CellValue(tmp,true);

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					if (type == xltypeBool)
					{
						bool tmp;

						xlret = xlrefij.element<XlfOper>(0UL,0UL).ConvertToBool(tmp);

						output(i,j) = tmp;

						if (xlret != xlretSuccess)
							return xlret;
					}
					else
					{
						char* tmp;
						if (type == xltypeStr || type == xltypeSRef)
						{
							xlret = xlrefij.element<XlfOper>(0UL,0UL).ConvertToString(tmp);
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
					xlret = ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToDouble(tmp);

					output(i,j) = tmp;

					if (xlret != xlretSuccess)
						return xlret;
				}
				else
				{
					char* tmp;
					if (type == xltypeStr || type == xltypeSRef)
					{
						xlret = ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j)).ConvertToString(tmp);
						output(i,j) = std::string(tmp);

						if (xlret != xlretSuccess)
							return xlret;
					} 
					else
					{
						if (ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j)).lpxloper12_->xltype != xltypeMissing)
							return xlretInvXloper;

					}

				}
		}

	}  
	return xlret;

}

int XlfOperImpl12::ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeErr)
  {
    e = xlfOper.lpxloper12_->val.err ;
    xlret = xlretSuccess;
  }
  else
  {
    // see ConvertToDouble
    XLOPER12 tmp;
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOper, xltypeErr, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToErr(e);
  }
  return xlret;
};

int XlfOperImpl12::ConvertToString(const XlfOper &xlfOper, char *& s) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeStr)
  {
    size_t n = xlfOper.lpxloper12_->val.str[0];
    s = XlfExcel::Instance().GetMemory(n + 1);
    wcstombs(s, xlfOper.lpxloper12_->val.str + 1, n);
    s[n] = 0;
    xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER12 tmp;
    // Second argument true marks XlfOper so that xlFree is called on the
    // MS Excel allocated memory (the string) when XlfOper goes out of scope.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOper, xltypeStr, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToString(s);
  }
  return xlret;
}

int XlfOperImpl12::ConvertToRef(const XlfOper &xlfOper, XlfRef& r) const throw()
{
  int xlret;

  if (xlfOper.lpxloper12_ == 0)
    return xlretInvXloper;

  if (xlfOper.lpxloper12_->xltype & xltypeRef)
  {
    const XLREF12& ref=xlfOper.lpxloper12_->val.mref.lpmref->reftbl[0];
    r = XlfRef (ref.rwFirst,  // top
                ref.colFirst, // left
                ref.rwLast,   // bottom
                ref.colLast,  // right
                xlfOper.lpxloper12_->val.mref.idSheet); // sheet id
    xlret = xlretSuccess;
  }
  else
  {
    // see AsDouble
    XLOPER12 tmp;
    // Second argument true marks XlfOper so that xlFree is called on the
    // MS Excel allocated memory (the reference array) when XlfOper goes
    // out of scope.
    XlfOper cast(&tmp);
    xlret = Coerce(xlfOper, xltypeRef, cast);
    if (xlret == xlretSuccess)
      xlret = cast.ConvertToRef(r);
  }
  return xlret;
}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, const CellMatrix& cells) const
{
    int r = cells.RowsInStructure();
    int c = cells.ColumnsInStructure();

	c = c < 255 ? c : 255;

    xlfOper.lpxloper12_->xltype = xltypeMulti;
    xlfOper.lpxloper12_->val.array.rows = r;
    xlfOper.lpxloper12_->val.array.columns = c; 

    xlfOper.lpxloper12_->val.array.lparray 
            = (LPXLOPER12)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER12));

    for (int i=0; i < r; i++)
        for (int j=0; j < c; j++)
        {
            int k = i*c +j;
            if (cells(i,j).IsANumber())
                xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).NumericValue());
            else
                if (cells(i,j).IsAString())
                    xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).StringValue());
                else
                if (cells(i,j).IsAWstring())
                    xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).WstringValue());
                else
					if (cells(i,j).IsBoolean())
						    xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper(cells(i,j).BooleanValue());
					else
						if (cells(i,j).IsError())
							 xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper(static_cast<WORD>(cells(i,j).ErrorValue()),true);
						else               
					            xlfOper.lpxloper12_->val.array.lparray[k] = *(LPXLOPER12)XlfOper("");
        }

    return xlfOper;

}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const
{
  assert(lpxlfoper != 0);
  xlfOper.lpxloper12_ = reinterpret_cast<LPXLOPER12>(lpxlfoper);
  return xlfOper;
}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, double value) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeNum;
    xlfOper.lpxloper12_->val.num = value;
  }
  return xlfOper;
}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, short value) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeInt;
    xlfOper.lpxloper12_->val.w = value;
  }
  return xlfOper;
}

//! bool for disambiguation
XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, short value, bool Error) const
{
  if (xlfOper.lpxloper12_)
  {
	if (Error)
	{
		xlfOper.lpxloper12_->xltype = xltypeErr;
		xlfOper.lpxloper12_->val.err =value;
	}
	else
	{
		xlfOper.lpxloper12_->xltype = xltypeInt;
		xlfOper.lpxloper12_->val.w = value;
	}
  }
  return xlfOper;
}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, bool value) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeBool;
    xlfOper.lpxloper12_->val.xbool = value;
  }
  return xlfOper;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the XlfRef is not copied.
*/
XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, const XlfRef& range) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeRef;
    XLMREF12 * pmRef = reinterpret_cast<XLMREF12 *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF12)));
    // if no memory is available
    if (pmRef == 0)
    {
      // set XlfOper to an invalid state
      xlfOper.lpxloper12_=0;
    }
    else
    {
      pmRef->count=1;
      pmRef->reftbl[0].rwFirst = range.GetRowBegin();
      pmRef->reftbl[0].rwLast = range.GetRowEnd()-1;
      pmRef->reftbl[0].colFirst = range.GetColBegin();
      pmRef->reftbl[0].colLast = range.GetColEnd()-1;
      xlfOper.lpxloper12_->val.mref.lpmref = pmRef;
      xlfOper.lpxloper12_->val.mref.idSheet = range.GetSheetId();
    }
  }
  return xlfOper;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the string is not copied.
*/
XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, const char *value) const
{
  if (xlfOper.lpxloper12_)
  {
    int len = strlen(value);
    xlfOper.lpxloper12_->val.str = (XCHAR*)XlfExcel::Instance().GetMemory((len+1)*2);
    if (xlfOper.lpxloper12_->val.str) {
        xlfOper.lpxloper12_->xltype = xltypeStr;
        mbstowcs(xlfOper.lpxloper12_->val.str + 1, value, len);
        xlfOper.lpxloper12_->val.str[0] = len;
    } else {
        xlfOper.lpxloper12_ = 0;
    }
  }
  return xlfOper;
}

XlfOper& XlfOperImpl12::Set(XlfOper &xlfOper, const std::wstring &value) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeStr;
    xlfOper.lpxloper12_->val.str = (XCHAR*)XlfExcel::Instance().GetMemory((value.length()+1)*2);
    wcsncpy(xlfOper.lpxloper12_->val.str + 1, value.c_str(), value.length());
    xlfOper.lpxloper12_->val.str[0] = value.length();
  }
  return xlfOper;
}

/*!
\sa XlfOper::Error(WORD)
*/
XlfOper& XlfOperImpl12::SetError(XlfOper &xlfOper, WORD error) const
{
  if (xlfOper.lpxloper12_)
  {
    xlfOper.lpxloper12_->xltype = xltypeErr;
    xlfOper.lpxloper12_->val.err = error;
  }
  return xlfOper;
}

XlfOper& XlfOperImpl12::assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const
{
  //if (xlfOper != &rhs) FIXME
    xlfOper.lpxloper12_ = rhs.lpxloper12_;
  return xlfOper;
}

LPXLOPER XlfOperImpl12::operator_LPXLOPER(const XlfOper &xlfOper) const
{
  throw("Unable to convert Excel 12 datatype to Excel 4 datatype - operation not yet implemented");
}

LPXLOPER12 XlfOperImpl12::operator_LPXLOPER12(const XlfOper &xlfOper) const
{
  return xlfOper.lpxloper12_;
}

LPXLFOPER XlfOperImpl12::operator_LPXLFOPER(const XlfOper &xlfOper) const
{
  return xlfOper.lpxloper12_;
}

bool XlfOperImpl12::IsMissing(const XlfOper &xlfOper) const
{
  return xlfOper.lpxloper12_->xltype == xltypeMissing;
}

bool XlfOperImpl12::IsError(const XlfOper &xlfOper) const
{
  return xlfOper.lpxloper12_->xltype == xltypeErr;
}

LPXLFOPER XlfOperImpl12::GetLPXLFOPER(const XlfOper &xlfOper) const
{
  return xlfOper.lpxloper12_;
}
