
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007 Tim Brunne
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
\file XlfOper4.cpp
\brief Implements the XlfOper4 class.
*/

// $Id: XlfOper4.cpp 383 2007-11-22 23:19:24Z ericehlers $

#include <xlw/XlfOper4.h>
#include <xlw/XlfException.h>
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

#ifndef NDEBUG
#include <xlw/XlfOper4.inl>
#endif

int xlw::XlfOper4::xlbitFreeAuxMem = 0x8000;

xlw::XlfOper4::XlfOper4(LPXLOPER lpxloper): lpxloper_(lpxloper)
{}

xlw::XlfOper4::~XlfOper4()
{
    if (! lpxloper_)
        return;

    int type = lpxloper_->xltype;

    if (type & xlbitFreeAuxMem)
    {
        // switch back the bit as it was originally
        lpxloper_->xltype &= ~xlbitFreeAuxMem;
        FreeAuxiliaryMemory();
    }
    Deallocate();
    return;
}

int xlw::XlfOper4::Allocate()
{
    lpxloper_ = (LPXLOPER)XlfExcel::Instance().GetMemory(sizeof(XLOPER));
    if (!lpxloper_)
        return xlretInvXloper;
    lpxloper_->xltype = xltypeNil;
    return xlretSuccess;
}

void xlw::XlfOper4::FreeAuxiliaryMemory() const
{
    int err = XlfExcel::Instance().XlfExcel::Instance().Call(xlFree, NULL, 1, (LPXLOPER)lpxloper_);
    if (err != xlretSuccess)
        std::cerr << XLW__HERE__ << "Call to xlFree failed" << std::endl;
    return;
}

int xlw::XlfOper4::Coerce(short type, XlfOper4& result) const
{
    XlfOper4 xlType(type);
    int xlret = XlfExcel::Instance().Call(xlCoerce, (LPXLOPER)result, 2, (LPXLOPER)lpxloper_, (LPXLOPER)xlType);
    return xlret;
}

double xlw::XlfOper4::AsDouble(int * pxlret) const
{
    double d;
    int xlret = ConvertToDouble(d);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return d;
};

double xlw::XlfOper4::AsDouble(const std::string& ErrorId, int * pxlret) const
{
    double d;
    int xlret = ConvertToDouble(d);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError( xlret,"Conversion to double "+ErrorId);
    return d;
};

int xlw::XlfOper4::ConvertToDouble(double& d) const throw()
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
        // Creates a XlfOper4 based on tmp.
        XlfOper4 cast(&tmp);
        // Coerces to numeric type.
        xlret = Coerce(xltypeNum,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToDouble(d);
    }
    return xlret;
};

xlw::MyArray xlw::XlfOper4::AsArray(DoubleVectorConvPolicy policy, int * pxlret) const
{
    std::vector<double> tmp(AsDoubleVector(policy,pxlret));
    MyArray result(tmp.size());
    for (unsigned long i=0; i < result.size(); i++)
        result[i] = tmp[i];

    return result;
}

xlw::MyArray xlw::XlfOper4::AsArray(const std::string& ErrorId,DoubleVectorConvPolicy policy, int * pxlret ) const
{
    std::vector<double> tmp(AsDoubleVector(ErrorId,policy,pxlret));
    MyArray result(tmp.size());
    for (unsigned long i=0; i < result.size(); i++)
        result[i] = tmp[i];

    return result;
}

std::vector<double> xlw::XlfOper4::AsDoubleVector(DoubleVectorConvPolicy policy, int * pxlret) const
{
    std::vector<double> v;
    int xlret = ConvertToDoubleVector(v, policy);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return v;
}

std::vector<double> xlw::XlfOper4::AsDoubleVector(const std::string& ErrorId, DoubleVectorConvPolicy policy, int * pxlret) const
{
    std::vector<double> v;
    int xlret = ConvertToDoubleVector(v, policy);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to double vector");
    return v;
}

int xlw::XlfOper4::ConvertToDoubleVector(std::vector<double>& v, DoubleVectorConvPolicy policy) const
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

    if (lpxloper_->xltype & xltypeMulti)
    {
        size_t nbRows = lpxloper_->val.array.rows;
        size_t nbCols = lpxloper_->val.array.columns;

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

                unsigned long thisType = (*lpxloper_).val.array.lparray[i*nbCols+j].xltype;
                if (thisType == xltypeNum)
                {
                    v[index] = (*lpxloper_).val.array.lparray[i*nbCols+j].val.num;
                }
                else
                {
                    v[index] = XlfOper(&(*lpxloper_).val.array.lparray[i*nbCols+j]).AsDouble();
                }
            }
        }
        return xlretSuccess;
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
            xlret = ref.element<XlfOper4>(i,j).ConvertToDouble(v[i*nbCols+j]);
        else
            // Fortran-like dense matrix storage. Does not matter if the policy is UniDimensional
            xlret = ref.element<XlfOper4>(i,j).ConvertToDouble(v[j*nbRows+i]);
        if (xlret != xlretSuccess)
            return xlret;
        }
    }
    return xlret;
};

short xlw::XlfOper4::AsShort(int * pxlret) const
{
    short s;
    int xlret = ConvertToShort(s);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return s;
};

short xlw::XlfOper4::AsShort(const std::string& ErrorId, int * pxlret) const
{
    short s;
    int xlret = ConvertToShort(s);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to short failed");
    return s;
};
int xlw::XlfOper4::ConvertToShort(short& s) const throw()
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
        // Creates a XlfOper4 based on tmp.
        XlfOper4 cast(&tmp);
        // Coerces to numeric type.
        xlret = Coerce(xltypeNum,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToShort(s);
    }
    return xlret;
};

bool xlw::XlfOper4::AsBool(int * pxlret) const
{
    bool b;
    int xlret = ConvertToBool(b);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return b;
};

bool xlw::XlfOper4::AsBool(const std::string& ErrorId, int * pxlret) const
{
    bool b;
    int xlret = ConvertToBool(b);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to bool failed");
    return b;
};

int xlw::XlfOper4::ConvertToBool(bool& b) const throw()
{
    int xlret;

    if (lpxloper_ == 0)
        return xlretInvXloper;

    if (lpxloper_->xltype & xltypeBool)
    {
        b = (lpxloper_->val.xbool != 0);
        xlret = xlretSuccess;
    }
    else
    {
        // see ConvertToDouble
        XLOPER tmp;
        XlfOper4 cast(&tmp);
        xlret = Coerce(xltypeBool,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToBool(b);
    }
    return xlret;
};

xlw::MyMatrix xlw::XlfOper4::AsMatrix( int * pxlret) const
{
    MyMatrix output; // will be resized anyway
    int xlret = ConvertToMatrix(output);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret," conversion to matrix failed");
    return output;
}

xlw::MyMatrix xlw::XlfOper4::AsMatrix( const std::string& ErrorId, int * pxlret) const
{
    MyMatrix output; // will be resized anyway
    int xlret = ConvertToMatrix(output);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to matrix failed");
    return output;
}

int xlw::XlfOper4::ConvertToMatrix(MyMatrix& value) const
{
    // deal with empty case first
    if (lpxloper_->xltype == xltypeMissing || lpxloper_->xltype == xltypeNil )
    {

        MyMatrix tmp;
        value = tmp;

        return xlretSuccess;
    }

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

xlw::CellMatrix xlw::XlfOper4::AsCellMatrix( int * pxlret) const
{
    CellMatrix output(1,1); // will be resized anyway
    int xlret = ConvertToCellMatrix(output);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret," conversion to cell matrix failed");
    return output;
}

xlw::CellMatrix xlw::XlfOper4::AsCellMatrix( const std::string& ErrorId, int * pxlret) const
{
    CellMatrix output(1,1); // will be resized anyway
    int xlret = ConvertToCellMatrix(output);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to cell matrix failed");
    return output;
}

int xlw::XlfOper4::ConvertToCellMatrix(CellMatrix& output) const
{

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

        tmp(0,0) = (lpxloper_->val.xbool >0);

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
                            result(i,j) = ((*lpxloper_).val.array.lparray[i*columns+j].val.xbool > 0);
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

    XlfRef ref;
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
            XlfOper4 element = ref.element<XlfOper4>(static_cast<WORD>(i), static_cast<BYTE>(j));
            unsigned long type = element.lpxloper_->xltype;

            if (type == xltypeRef)
            {
                XlfRef xlrefij;

                int xlretij = element.ConvertToRef(xlrefij);

                if (xlretij != xlretSuccess)
                    return xlretij;

                XlfOper4 refElement = xlrefij.element<XlfOper4>(0UL,0UL);
                type = refElement.lpxloper_->xltype;

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
                        if (element.lpxloper_->xltype != xltypeMissing)
                            return xlretInvXloper;

                    }

                }
        }

    }
    return xlret;

}

int xlw::XlfOper4::ConvertToErr(WORD& e) const throw()
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
        XlfOper4 cast(&tmp);
        xlret = Coerce(xltypeErr,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToErr(e);
    }
    return xlret;
};

char * xlw::XlfOper4::AsString(int * pxlret) const
{
    char * s;
    int xlret = ConvertToString(s);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return s;
};

char * xlw::XlfOper4::AsString(const std::string& ErrorId, int * pxlret) const
{
    char * s;
    int xlret = ConvertToString(s);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret,ErrorId+" conversion to char* failed");
    return s;
};

int xlw::XlfOper4::ConvertToString(char *& s) const throw()
{
    int xlret;

    if (lpxloper_ == 0)
        return xlretInvXloper;

    if (lpxloper_->xltype & xltypeStr)
    {
        // Must use datatype unsigned char (BYTE) to process 0th byte
        // otherwise numbers greater than 128 are incorrect
        size_t n = (unsigned char) lpxloper_->val.str[0];
        s = XlfExcel::Instance().GetMemory(n + 1);
        memcpy(s, lpxloper_->val.str + 1, n);
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
        XlfOper4 cast(&tmp);
        xlret = Coerce(xltypeStr,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToString(s);
    }
    return xlret;
}

xlw::XlfRef xlw::XlfOper4::AsRef(int * pxlret) const
{
    XlfRef r;
    int xlret = ConvertToRef(r);
    if (pxlret)
        *pxlret=xlret;
    else
        ThrowOnError(xlret);
    return r;
}

int xlw::XlfOper4::ConvertToRef(XlfRef& r) const throw()
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
        // Function Coerce calls function Call which sets bit xlbitFreeAuxMem of variable cast,
        // so that the memory which Excel allocates to that variable (the reference) is freed
        // when the variable goes out of scope.
        XlfOper4 cast(&tmp);
        xlret = Coerce(xltypeRef,cast);
        if (xlret == xlretSuccess)
            xlret = cast.ConvertToRef(r);
    }
    return xlret;
}

xlw::XlfOper4& xlw::XlfOper4::Set(const MyMatrix& values)
{
    if (values.size1() ==0 || values.size2() ==0)
    {
        return *this;
    }

    CellMatrix tmp(values.size1(), values.size2());
    for (unsigned long i=0; i < values.size1(); i++)
        for (unsigned long j=0; j < values.size2(); j++)
            tmp(i,j) = Element(values,i,j);
    return Set(tmp);
}

xlw::XlfOper4& xlw::XlfOper4::Set(const MyArray& values)
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

xlw::XlfOper4& xlw::XlfOper4::Set(const CellMatrix& cells)
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
                lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper4(cells(i,j).NumericValue());
            else
                if (cells(i,j).IsAString())
                    lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper4(cells(i,j).StringValue().c_str());
                else
                    if (cells(i,j).IsBoolean())
                            lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper4(cells(i,j).BooleanValue());
                    else
                        if (cells(i,j).IsError())
                             lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper4(static_cast<WORD>(cells(i,j).ErrorValue()),true);
                        else
                                lpxloper_->val.array.lparray[k] = *(LPXLOPER)XlfOper4("");
        }

    return *this;


}

xlw::XlfOper4& xlw::XlfOper4::Set(LPXLOPER lpxloper)
{
    assert(lpxloper != 0);
    lpxloper_ = lpxloper;
    return *this;
}

xlw::XlfOper4& xlw::XlfOper4::Set(double value)
{
    if (lpxloper_)
    {
        lpxloper_->xltype = xltypeNum;
        lpxloper_->val.num = value;
    }
    return *this;
}

xlw::XlfOper4& xlw::XlfOper4::Set(short value)
{
    if (lpxloper_)
    {
        lpxloper_->xltype = xltypeInt;
        lpxloper_->val.w = value;
    }
    return *this;
}

xlw::XlfOper4& xlw::XlfOper4::Set(short value, bool Error)
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

xlw::XlfOper4& xlw::XlfOper4::Set(bool value)
{
    if (lpxloper_)
    {
        lpxloper_->xltype = xltypeBool;
        lpxloper_->val.xbool = value;
    }
    return *this;
}

xlw::XlfOper4& xlw::XlfOper4::Set(const XlfRef& range)
{
    if (lpxloper_)
    {
        lpxloper_->xltype = xltypeRef;
        XLMREF * pmRef = reinterpret_cast<XLMREF *>(XlfExcel::Instance().GetMemory(sizeof(XLMREF)));
        // if no memory is available
        if (pmRef == 0)
        {
            // set XlfOper4 to an invalid state
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

xlw::XlfOper4& xlw::XlfOper4::Set(const char *value)
{
    if (lpxloper_)
    {
        unsigned int n = static_cast<unsigned int>(strlen(value));
        if (n > 254)
        {
            std::cerr << XLW__HERE__ << "String truncated to 254 bytes" << std::endl;
            n = 254;
        }
        // One byte more for NULL terminal char (allow use of strcpy)
        // and one for the std::string size (convention used by Excel)
        LPSTR str = reinterpret_cast<LPSTR>(XlfExcel::Instance().GetMemory(n + 2));
        if (str == 0)
        {
            lpxloper_=0;
        }
        else
        {
            strncpy(str + 1, value, n);
            str[n + 1] = 0;

            lpxloper_->val.str = str;
            lpxloper_->val.str[0] = (BYTE)(n + 1);
            lpxloper_->xltype = xltypeStr;
        }
    }
    return *this;
}

xlw::XlfOper4& xlw::XlfOper4::SetError(WORD error)
{
    if (lpxloper_)
    {
        lpxloper_->xltype = xltypeErr;
        lpxloper_->val.err = error;
    }
    return *this;
}

int xlw::XlfOper4::ThrowOnError(int xlret) const
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
    // should never get here.
    assert(0);
    return xlret;
}

int xlw::XlfOper4::ThrowOnError(int xlret, const std::string& Identifier) const
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
    // should never get here.
    assert(0);
    return xlret;
}

WORD xlw::XlfOper4::xltype() const {
    if (lpxloper_)
        return lpxloper_->xltype;
    else
        return 0;
}

