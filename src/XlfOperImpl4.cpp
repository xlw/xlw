
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers

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
\file XlfOperImpl4.cpp
\brief Implements the XlfOperImpl4 class.
*/

// $Id: XlfOper.cpp 335 2007-06-25 03:47:43Z markjoshi $

#include <xlw/XlfOper.h>
#include <xlw/XlfOperImpl4.h>
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
void XlfOperImpl4::destroy(const XlfOper &xlfOper) const
{
    if (!xlfOper.lpxloper4_)
        return;

    int type = xlfOper.lpxloper4_->xltype;

    //  Only the types below can be flagged xlFreeAuxMem, thus the test is
    //  actually redundant: we don't need to re-check the type of the oper.
    //
    //bool canHaveAuxMem = (type & xltypeStr ||
    //                      type & xltypeRef ||
    //                      type & xltypeMulti ||
    //                      type & xltypeBigData);
    if (type & XlfOper::xlbitFreeAuxMem)
    {
        // switch back the bit as it was originally
        xlfOper.lpxloper4_->xltype &= ~XlfOper::xlbitFreeAuxMem;
        FreeAuxiliaryMemory(xlfOper);
    }
    return;
}

/*!
Allocates 16 bytes (size of an XLOPER) on the temporary buffer
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
int XlfOperImpl4::Allocate(XlfOper &xlfOper) const
{
    xlfOper.lpxloper4_ = (LPXLOPER)XlfExcel::Instance().GetMemory(sizeof(XLOPER));
    if (!xlfOper.lpxloper4_)
        return xlretInvXloper;
    xlfOper.lpxloper4_->xltype = xltypeNil;
    return xlretSuccess;
}

void XlfOperImpl4::FreeAuxiliaryMemory(const XlfOper &xlfOper) const
{
    int err = XlfExcel::Instance().XlfExcel::Instance().Call(xlFree, NULL, 1, (LPXLFOPER)xlfOper.lpxloper4_);
    if (err != xlretSuccess)
        std::cerr << XLW__HERE__ << "Call to xlFree failed" << std::endl;
    return;
}

/*!
\param type is an integer indicating the target type we want to coerce to.
\param result is the XLOPER where to store the output.
*/
int XlfOperImpl4::Coerce(const XlfOper &xlfOper, short type, XlfOper& result) const
{
    XlfOper xlType(type);
    // FIXME call4?
    int xlret = XlfExcel::Instance().Call(xlCoerce, (LPXLFOPER)result, 2, (LPXLFOPER)xlfOper.lpxloper4_, (LPXLFOPER)xlType);
    return xlret;
}

int XlfOperImpl4::ConvertToDouble(const XlfOper &xlfOper, double& d) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeInt)
    {
        d = xlfOper.lpxloper4_->val.w;
        xlret=xlretSuccess;
    }
    else if (xlfOper.lpxloper4_->xltype & xltypeNum)
    {
        d = xlfOper.lpxloper4_->val.num;
        xlret=xlretSuccess;
    }
    else
    {
        // Allocates tmp on the stack to avoid filling the internal buffer.
        XLOPER tmp;
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
int XlfOperImpl4::ConvertToDoubleVector(const XlfOper &xlfOper, std::vector<double>& v, DoubleVectorConvPolicy policy) const
{
    if (xlfOper.lpxloper4_->xltype == xltypeMissing)
    {
        v.resize(0);
        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype & xltypeNum)
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

    if (xlfOper.lpxloper4_->xltype & xltypeMulti)
    {
        size_t nbRows = xlfOper.lpxloper4_->val.array.rows;
        size_t nbCols = xlfOper.lpxloper4_->val.array.columns;

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

                unsigned long thisType = (*xlfOper.lpxloper4_).val.array.lparray[i*nbCols+j].xltype;
                if (thisType == xltypeNum)
                {
                    v[index] = (*xlfOper.lpxloper4_).val.array.lparray[i*nbCols+j].val.num;
                }
                else
                {
                    int xlret =  XlfOper(&(*xlfOper.lpxloper4_).val.array.lparray[i*nbCols+j]).ConvertToDouble(v[index]);
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

int XlfOperImpl4::ConvertToShort(const XlfOper &xlfOper, short& s) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeNum)
    {
        s = static_cast<short>(xlfOper.lpxloper4_->val.num);
        xlret=xlretSuccess;
    }
    else
    {
        // Allocates tmp on the stack to avoid filling the internal buffer.
        XLOPER tmp;
        // Creates a XlfOper based on tmp.
        XlfOper cast(&tmp);
        // Coerces to numeric type.
        xlret = Coerce(xlfOper, xltypeNum, cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToShort(s);
    }
    return xlret;
};

int XlfOperImpl4::ConvertToBool(const XlfOper &xlfOper, bool& b) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeBool)
    {
        b = (xlfOper.lpxloper4_->val.xbool != 0);
        xlret = xlretSuccess;
    }
    else
    {
        // see ConvertToDouble
        XLOPER tmp;
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
int XlfOperImpl4::ConvertToMatrix(const XlfOper &xlfOper, MyMatrix& value) const
{
    // deal with empty case first
    if (xlfOper.lpxloper4_->xltype == xltypeMissing || xlfOper.lpxloper4_->xltype == xltypeNil )
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

int XlfOperImpl4::ConvertToCellMatrix(const XlfOper &xlfOper, CellMatrix& output) const
{

    if (xlfOper.lpxloper4_->xltype == xltypeMissing || xlfOper.lpxloper4_->xltype == xltypeNil)
    {

        CellMatrix tmp(1,1);
        output = tmp;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype == xltypeNum)
    {
        CellMatrix tmp(1,1);

        tmp(0,0) = xlfOper.lpxloper4_->val.num;

        output = tmp;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype == xltypeBool)
    {
        CellMatrix tmp(1,1);

        tmp(0,0) = (xlfOper.lpxloper4_->val.xbool >0);

        output = tmp;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype == xltypeErr)
    {
        CellMatrix tmp(1,1);

        tmp(0,0) = CellValue(xlfOper.lpxloper4_->val.err, true);

        output = tmp;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype == xltypeStr)
    {
        CellMatrix tmpCell(1,1);

        unsigned long len = *((*xlfOper.lpxloper4_).val.str);

        std::string tmp;
        tmp.resize(len);

        for(unsigned long k=0; k<len; ++k)
            tmp[k]= ((*xlfOper.lpxloper4_).val.str)[k+1];

        tmpCell(0,0) = tmp;

        output = tmpCell;

        return xlretSuccess;
    }

    if (xlfOper.lpxloper4_->xltype == xltypeMulti)
    {
        unsigned long rows = xlfOper.lpxloper4_->val.array.rows;
        unsigned long columns = xlfOper.lpxloper4_->val.array.columns;
        CellMatrix result(rows,columns);

        for (unsigned long i=0; i < rows; i++)
            for (unsigned long j=0; j < columns; j++)
            {
                unsigned long thisType = (*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].xltype;
                if (thisType == xltypeNum)
                {
                    double x = (*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].val.num;
                    result(i,j) = x;
                }
                else
                {
                    if (thisType==xltypeStr)
                    {
                          unsigned long len = *((*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].val.str);

                          std::string tmp;
                          tmp.resize(len);

                          for(unsigned long k=0; k<len; ++k)
                            tmp[k]=
                            ((*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].val.str)[k+1];

                          result(i,j) = tmp;
                    }

                    else
                        if (thisType == xltypeBool)
                        {
                            result(i,j) = ((*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].val.xbool > 0);
                        }
                        else
                            if (thisType== xltypeErr)
                            {
                                result(i,j) = CellValue(((*xlfOper.lpxloper4_).val.array.lparray[i*columns+j].val.err),true);
                            }
                            else
                                if (thisType!=xltypeMissing && thisType != xltypeNil)
                                    throw("cell contains neither number nor string nor boolean nor empty");
                }

            }

        output= result;

        return xlretSuccess;

    }

    XlfRef ref;

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
            XlfOper element = ref.element<XlfOper>(static_cast<WORD>(i),static_cast<BYTE>(j));
            unsigned long type = element.lpxloper4_->xltype;

            if (type == xltypeRef)
            {
                XlfRef xlrefij;

                int xlretij = element.ConvertToRef(xlrefij);

                if (xlretij != xlretSuccess)
                    return xlretij;

                XlfOper refElement = xlrefij.element<XlfOper>(0UL,0UL);
                type = refElement.lpxloper4_->xltype;

                if (type == xltypeNum)
                {
                    double tmp;
                    xlret = refElement.ConvertToDouble(tmp);

                    output(i,j) = tmp;

                    if (xlret != xlretSuccess)
                        return xlret;
                }
                else
                    if (type == xltypeErr)
                    {
                        WORD tmp;

                        xlret = refElement.ConvertToErr(tmp);

                        output(i,j) = CellValue(tmp,true);

                        if (xlret != xlretSuccess)
                            return xlret;
                    }
                    else
                    if (type == xltypeBool)
                    {
                        bool tmp;

                        xlret = refElement.ConvertToBool(tmp);

                        output(i,j) = tmp;

                        if (xlret != xlretSuccess)
                            return xlret;
                    }
                    else
                    {
                        if (type == xltypeStr || type == xltypeSRef)
                        {
                            char* tmp;
                            xlret = refElement.ConvertToString(tmp);
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
                    xlret = element.ConvertToDouble(tmp);

                    output(i,j) = tmp;

                    if (xlret != xlretSuccess)
                        return xlret;
                }
                else
                {
                    if (type == xltypeStr || type == xltypeSRef)
                    {
                        char* tmp;
                        xlret = element.ConvertToString(tmp);
                        output(i,j) = std::string(tmp);

                        if (xlret != xlretSuccess)
                            return xlret;
                    }
                    else
                    {
                        if (element.lpxloper4_->xltype != xltypeMissing)
                            return xlretInvXloper;

                    }

                }
        }

    }
    return xlret;

}

int XlfOperImpl4::ConvertToErr(const XlfOper &xlfOper, WORD& e) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeErr)
    {
        e = xlfOper.lpxloper4_->val.err ;
        xlret = xlretSuccess;
    }
    else
    {
        // see ConvertToDouble
        XLOPER tmp;
        XlfOper cast(&tmp);
        xlret = Coerce(xlfOper, xltypeErr, cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToErr(e);
    }
    return xlret;
};

int XlfOperImpl4::ConvertToString(const XlfOper &xlfOper, char *& s) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeStr)
    {
        // Must use datatype unsigned char (BYTE) to process 0th byte
        // otherwise numbers greater than 128 are incorrect
        size_t n = (unsigned char) xlfOper.lpxloper4_->val.str[0];
        s = XlfExcel::Instance().GetMemory(n + 1);
        memcpy(s, xlfOper.lpxloper4_->val.str + 1, n);
        s[n] = 0;
        xlret = xlretSuccess;
    }
    else
    {
        // see AsDouble
        XLOPER tmp;
        // Function Coerce calls function Call which sets bit xlbitFreeAuxMem of variable cast,
        // so that the memory which Excel allocates to that variable (the string) is freed
        // when the variable goes out of scope.
        XlfOper cast(&tmp);
        xlret = Coerce(xlfOper, xltypeStr, cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToString(s);
    }
    return xlret;
}

int XlfOperImpl4::ConvertToWstring(const XlfOper &xlfOper, std::wstring &s) const throw()
{

    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeStr)
    {
        size_t n = (unsigned char) xlfOper.lpxloper4_->val.str[0];
        wchar_t *c = reinterpret_cast<wchar_t*>(XlfExcel::Instance().GetMemory(n*2+2));
        mbstowcs(c, xlfOper.lpxloper4_->val.str + 1, n*2);
        c[n]=0;
        s = std::wstring(c);
        xlret = xlretSuccess;
    }
    else
    {
        // see AsDouble
        XLOPER tmp;
        // Function Coerce calls function Call which sets bit xlbitFreeAuxMem of variable cast,
        // so that the memory which Excel allocates to that variable (the string) is freed
        // when the variable goes out of scope.
        XlfOper cast(&tmp);
        xlret = Coerce(xlfOper, xltypeStr, cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToWstring(s);
    }
    return xlret;
}

int XlfOperImpl4::ConvertToRef(const XlfOper &xlfOper, XlfRef& r) const throw()
{
    int xlret;

    if (xlfOper.lpxloper4_ == 0)
        return xlretInvXloper;

    if (xlfOper.lpxloper4_->xltype & xltypeRef)
    {
        const XLREF& ref=xlfOper.lpxloper4_->val.mref.lpmref->reftbl[0];
        r = XlfRef (ref.rwFirst,  // top
                    ref.colFirst, // left
                    ref.rwLast,   // bottom
                    ref.colLast,  // right
                    xlfOper.lpxloper4_->val.mref.idSheet); // sheet id
        xlret = xlretSuccess;
    }
    else
    {
        // see AsDouble
        XLOPER tmp;
        // Function Coerce calls function Call which sets bit xlbitFreeAuxMem of variable cast,
        // so that the memory which Excel allocates to that variable (the reference) is freed
        // when the variable goes out of scope.
        XlfOper cast(&tmp);
        xlret = Coerce(xlfOper, xltypeRef, cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToRef(r);
    }
    return xlret;
}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, const CellMatrix& cells) const
{
    int r = cells.RowsInStructure();
    int c = cells.ColumnsInStructure();

    c = c < 255 ? c : 255;

    xlfOper.lpxloper4_->xltype = xltypeMulti;
    xlfOper.lpxloper4_->val.array.rows = r;
    xlfOper.lpxloper4_->val.array.columns = c;

    xlfOper.lpxloper4_->val.array.lparray
            = (LPXLOPER)XlfExcel::Instance().GetMemory(r*c*sizeof(XLOPER));

    for (int i=0; i < r; i++)
        for (int j=0; j < c; j++)
        {
            int k = i*c +j;
            if (cells(i,j).IsANumber())
                xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).NumericValue());
            else
                if (cells(i,j).IsAString() || cells(i,j).IsAWstring())
                    xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).StringValue().c_str());
                else
                    if (cells(i,j).IsBoolean())
                            xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).BooleanValue());
                    else
                        if (cells(i,j).IsXlfOper())
                             xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper(cells(i,j).XlfOperValue().GetLPXLFOPER());
                        else
                        if (cells(i,j).IsError())
                             xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper(static_cast<WORD>(cells(i,j).ErrorValue()),true);
                        else
                                xlfOper.lpxloper4_->val.array.lparray[k] = *(LPXLOPER)XlfOper("");
        }

    return xlfOper;

}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, LPXLFOPER lpxlfoper) const
{
    assert(lpxlfoper != 0);
    xlfOper.lpxloper4_ = reinterpret_cast<LPXLOPER>(lpxlfoper);
    return xlfOper;
}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, double value) const
{
    if (xlfOper.lpxloper4_)
    {
        xlfOper.lpxloper4_->xltype = xltypeNum;
        xlfOper.lpxloper4_->val.num = value;
    }
    return xlfOper;
}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, short value) const
{
    if (xlfOper.lpxloper4_)
    {
        xlfOper.lpxloper4_->xltype = xltypeInt;
        xlfOper.lpxloper4_->val.w = value;
    }
    return xlfOper;
}

//! bool for disambiguation
XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, short value, bool Error) const
{
    if (xlfOper.lpxloper4_)
    {
        if (Error)
        {
            xlfOper.lpxloper4_->xltype = xltypeErr;
            xlfOper.lpxloper4_->val.err =value;
        }
        else
        {
            xlfOper.lpxloper4_->xltype = xltypeInt;
            xlfOper.lpxloper4_->val.w = value;
        }
    }
    return xlfOper;
}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, bool value) const
{
    if (xlfOper.lpxloper4_)
    {
        xlfOper.lpxloper4_->xltype = xltypeBool;
        xlfOper.lpxloper4_->val.xbool = value;
    }
    return xlfOper;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the XlfRef is not copied.
*/
XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, const XlfRef& range) const
{
    if (xlfOper.lpxloper4_)
    {
        xlfOper.lpxloper4_->xltype = xltypeRef;
        XLMREF * pmRef = reinterpret_cast<XLMREF *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF)));
        // if no memory is available
        if (pmRef == 0)
        {
            // set XlfOper to an invalid state
            xlfOper.lpxloper4_=0;
        }
        else
        {
            pmRef->count=1;
            pmRef->reftbl[0].rwFirst = range.GetRowBegin();
            pmRef->reftbl[0].rwLast = range.GetRowEnd()-1;
            pmRef->reftbl[0].colFirst = range.GetColBegin();
            pmRef->reftbl[0].colLast = range.GetColEnd()-1;
            xlfOper.lpxloper4_->val.mref.lpmref = pmRef;
            xlfOper.lpxloper4_->val.mref.idSheet = range.GetSheetId();
        }
    }
    return xlfOper;
}

/*!
If no memory can be allocated on xlw internal buffer, the XlfOper is set
to an invalid state and the string is not copied.

The Excel API supports strings of 256 bytes.  The 0th byte holds the length
of the string and the remaining 255 bytes hold the string data which is not
null terminated.

Here xlw uses the 0th byte for the string length, then at the 1st byte
starts a string which _is_ null terminated.  In theory this allows a pointer
to the 1st byte to be passed to C string functions requiring null termination
e.g. strcpy.

\note A string longer than 254 characters is truncated. A warning
is issued in debug mode.
*/
XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, const char *value) const
{
    if (xlfOper.lpxloper4_)
    {
        unsigned int n = static_cast<unsigned int>(strlen(value));

        if (n > 254)
        {
            std::cerr << XLW__HERE__ << "String truncated to 254 bytes" << std::endl;
            n = 254;
        }
        // One byte more for the string length (convention used by Excel)
        // and one for the NULL terminal char (allow use of strcpy)
        LPSTR str = reinterpret_cast<LPSTR>(XlfExcel::Instance().GetMemory(n + 2));
        if (str == 0)
        {
            xlfOper.lpxloper4_=0;
        }
        else
        {
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif
            strncpy(str + 1, value, n);
            str[n + 1] = 0;

            xlfOper.lpxloper4_->val.str = str;
            xlfOper.lpxloper4_->val.str[0] = (BYTE)(n + 1);
            xlfOper.lpxloper4_->xltype = xltypeStr;
        }
    }
    return xlfOper;
}

XlfOper& XlfOperImpl4::Set(XlfOper &xlfOper, const std::wstring &value) const
{
    if (xlfOper.lpxloper4_)
    {

        unsigned int n;
        if (value.length() > 255)
        {
            std::cerr << XLW__HERE__ << "String truncated to 255 bytes" << std::endl;
            n = 255;
        } else {
            n = value.length();
        }

        // One byte more for the string length (convention used by Excel)
        LPSTR str = reinterpret_cast<LPSTR>(XlfExcel::Instance().GetMemory(n + 1));
        if (str == 0)
        {
            xlfOper.lpxloper4_=0;
        }
        else
        {
            wcstombs(str + 1, value.c_str(), n);
            xlfOper.lpxloper4_->val.str = str;
            xlfOper.lpxloper4_->val.str[0] = (BYTE)(n);
            xlfOper.lpxloper4_->xltype = xltypeStr;
        }
    }
    return xlfOper;
}

/*!
\sa XlfOper::Error(WORD)
*/
XlfOper& XlfOperImpl4::SetError(XlfOper &xlfOper, WORD error) const
{
    if (xlfOper.lpxloper4_)
    {
        xlfOper.lpxloper4_->xltype = xltypeErr;
        xlfOper.lpxloper4_->val.err = error;
    }
    return xlfOper;
}

XlfOper& XlfOperImpl4::assignment_operator(XlfOper &xlfOper, const XlfOper &rhs) const
{
    //if (xlfOper != &rhs) FIXME
        xlfOper.lpxloper4_ = rhs.lpxloper4_;
    return xlfOper;
}

LPXLOPER XlfOperImpl4::operator_LPXLOPER(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_;
}

LPXLOPER12 XlfOperImpl4::operator_LPXLOPER12(const XlfOper &xlfOper) const
{
    throw("Unable to convert Excel 4 datatype to Excel 12 datatype - operation not yet implemented");
}

LPXLFOPER XlfOperImpl4::operator_LPXLFOPER(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_;
}

bool XlfOperImpl4::IsMissing(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeMissing;
}

bool XlfOperImpl4::IsError(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeErr;
}

bool XlfOperImpl4::IsRef(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeRef;
}

bool XlfOperImpl4::IsSRef(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeSRef;
}

bool XlfOperImpl4::IsMulti(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeMulti;
}

bool XlfOperImpl4::IsNumber(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeNum;
}

bool XlfOperImpl4::IsString(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeStr;
}

bool XlfOperImpl4::IsNil(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeNil;
}

bool XlfOperImpl4::IsBool(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeBool;
}

bool XlfOperImpl4::IsInt(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_->xltype & xltypeInt;
}

LPXLFOPER XlfOperImpl4::GetLPXLFOPER(const XlfOper &xlfOper) const
{
    return xlfOper.lpxloper4_;
}

DWORD XlfOperImpl4::xltype(const XlfOper &xlfOper) const {
    if (xlfOper.lpxloper4_)
        return xlfOper.lpxloper4_->xltype;
    else
        return 0;
}

