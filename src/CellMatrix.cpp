//
//
//                        CellMatrix.cpp
//
//
/*
 Copyright (C) 2006 Mark Joshi
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
#include <xlw/CellMatrix.h>
#include <algorithm>

unsigned long maxi(unsigned long a, unsigned long b)
{
    return a > b ? a : b;
}

bool xlw::CellValue::IsAString() const
{
    return Type == string;
}

bool xlw::CellValue::IsAWstring() const
{
    return Type == wstring;
}

bool xlw::CellValue::IsANumber() const
{
    return Type == number;
}

bool xlw::CellValue::IsBoolean() const
{
    return Type == boolean;
}

bool xlw::CellValue::IsXlfOper() const
{
    return Type == xlfoper;
}

bool xlw::CellValue::IsError() const
{
    return Type == error;
}

bool xlw::CellValue::IsEmpty() const
{
    return Type == empty;
}


xlw::CellValue::operator std::string() const
{
    if (Type != string)
        throw("non string cell asked to be a string");
    return ValueAsString;
}

xlw::CellValue::operator std::wstring() const
{
    if (Type != wstring)
        throw("non string cell asked to be a string");
    return ValueAsWstring;
}

xlw::CellValue::operator bool() const
{
    if (Type != boolean)
        throw("non boolean cell asked to be a bool");
    return ValueAsBool;
}

xlw::CellValue::operator double() const
{
    if (Type != number)
        throw("non number cell asked to be a number");
    return ValueAsNumeric;
}

xlw::CellValue::operator unsigned long() const
{
    if (Type != number)
        throw("non number cell asked to be a number");
    return static_cast<unsigned long>(ValueAsNumeric);
}

void xlw::CellValue::clear()
{
    Type = empty;
    ValueAsString="";
    ValueAsWstring=L"";
    ValueAsNumeric=0.0;
    ValueAsBool=false;
    ValueAsErrorCode=0;
}


xlw::CellValue::CellValue(const std::string& value) : Type(xlw::CellValue::string),
ValueAsString(value), ValueAsWstring(L""), ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::CellValue::CellValue(const std::wstring& value) : Type(xlw::CellValue::wstring),
ValueAsString(""), ValueAsWstring(value), ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::CellValue::CellValue(const char* value) : Type(xlw::CellValue::string),
ValueAsString(value), ValueAsWstring(L""), ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{

}
xlw::CellValue::CellValue(double Number): Type(xlw::CellValue::number),
ValueAsString(""), ValueAsWstring(L""), ValueAsNumeric(Number), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::CellValue::CellValue(int i): Type(xlw::CellValue::number),
ValueAsString(""), ValueAsWstring(L""), ValueAsNumeric(i), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::CellValue::CellValue(unsigned long Code, bool Error): Type(error),
ValueAsString(""), ValueAsWstring(L""), ValueAsNumeric(Code), ValueAsBool(false), ValueAsErrorCode(Code)
{
    if (!Error)
        Type = number;
}

xlw::CellValue::CellValue(bool TrueFalse)
 : Type(xlw::CellValue::boolean),
ValueAsString(""), ValueAsWstring(L""), ValueAsNumeric(0.0), ValueAsBool(TrueFalse), ValueAsErrorCode(0)
{
}

xlw::CellValue::CellValue(): Type(xlw::CellValue::empty),
ValueAsString(""), ValueAsWstring(L""), ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{
}

std::string xlw::CellValue::StringValue() const
{
    if (Type == string) {
        return ValueAsString;
    } else if (Type == wstring) {
        return std::string(ValueAsWstring.begin(), ValueAsWstring.end());
    } else {
        throw("non string cell asked to be a string");
    }
}

const std::wstring& xlw::CellValue::WstringValue() const
{
    if (Type != wstring)
        throw("non wstring cell asked to be a wstring");
    return ValueAsWstring;
}

double xlw::CellValue::NumericValue() const
{

    if (Type != number)
        throw("non number cell asked to be a number");
    return ValueAsNumeric;
}

bool xlw::CellValue::BooleanValue() const
{

    if (Type != boolean)
        throw("non boolean cell asked to be a bool");

    return ValueAsBool;
}

unsigned long xlw::CellValue::ErrorValue() const
{
    if (Type != error)
        throw("non error cell asked to be an error");

    return ValueAsErrorCode;
}

std::string xlw::CellValue::StringValueLowerCase() const
{
    if (Type == string) {
        std::string tmp(ValueAsString);
        std::transform(tmp.begin(),tmp.end(),tmp.begin(),tolower);
        return tmp;
    } else if (Type == wstring) {
        std::wstring w(WstringValueLowerCase());
        return std::string(w.begin(), w.end());
    } else {
        throw("non string cell asked to be a string");
    }
}

std::wstring xlw::CellValue::WstringValueLowerCase() const
{
    if (Type == string) {
        std::string s(StringValueLowerCase());
        return std::wstring(s.begin(), s.end());
    } else if (Type == wstring) {
        std::wstring tmp(ValueAsWstring);
        std::transform(tmp.begin(),tmp.end(),tmp.begin(),tolower);
        return tmp;
    } else {
        throw("non string cell asked to be a string");
    }
}

xlw::CellMatrix::CellMatrix() : Cells(0), Rows(0), Columns(0)
{
}

xlw::CellMatrix::CellMatrix(double x): Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(x));
}

xlw::CellMatrix::CellMatrix(std::string x): Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(x));
}

xlw::CellMatrix::CellMatrix(std::wstring x): Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(x));
}

xlw::CellMatrix::CellMatrix(const char* x): Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(x));
}

xlw::CellMatrix::CellMatrix(const MyArray& data) : Cells(data.size()),
    Rows(data.size()), Columns(1)
{
    for (unsigned long i=0; i < data.size(); ++i)
        Cells[i].push_back(CellValue(data[i]));
}

xlw::CellMatrix::CellMatrix(const MyMatrix& data): Cells(data.size1()),
    Rows(data.size1()), Columns(data.size2())
{
    for (unsigned long i=0; i < data.size1(); ++i)
        for (unsigned long j=0; j < data.size2(); ++j)
            Cells[i].push_back(CellValue(Element(data,i,j)));
}

xlw::CellMatrix::CellMatrix(unsigned long i)
    : Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(static_cast<double>(i)));
}

xlw::CellMatrix::CellMatrix(int i): Cells(1), Rows(1), Columns(1)
{
    Cells[0].push_back(CellValue(static_cast<double>(i)));
}

xlw::CellMatrix::CellMatrix(unsigned long rows, unsigned long columns)
    : Cells(rows), Rows(rows), Columns(columns)
{
    for (unsigned long i=0; i < rows; i++)
        Cells[i].resize(columns);
}

const xlw::CellValue& xlw::CellMatrix::operator()(unsigned long i, unsigned long j) const
{
    return Cells.at(i).at(j);

}
xlw::CellValue& xlw::CellMatrix::operator()(unsigned long i, unsigned long j)
{
    return Cells.at(i).at(j);
}

unsigned long xlw::CellMatrix::RowsInStructure() const
{
    return Rows;
}
unsigned long xlw::CellMatrix::ColumnsInStructure() const
{
    return Columns;
}

xlw::CellMatrix xlw::MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom)
{
    unsigned long cols = maxi(Top.ColumnsInStructure(), Bottom.ColumnsInStructure());
    unsigned long rows = Top.RowsInStructure()+Bottom.RowsInStructure();

    CellMatrix merged(rows,cols);

    {for (unsigned long i=0; i < Top.ColumnsInStructure(); i++)
        for (unsigned long j=0; j < Top.RowsInStructure(); j++)
            merged(j,i) = Top(j,i);}

    for (unsigned long i=0; i < Bottom.ColumnsInStructure(); i++)
        for (unsigned long j=0; j < Bottom.RowsInStructure(); j++)
            merged(j+Top.RowsInStructure(),i) = Bottom(j,i);

    return merged;
}

void xlw::CellMatrix::PushBottom(const CellMatrix& newRows)
{
    CellMatrix newRowsResize(newRows);
    unsigned long newColumns = maxi(newRows.ColumnsInStructure(),Columns);

    if (newColumns > Columns)
        for (unsigned long i=0; i < Rows; i++)
            Cells[i].resize(newColumns);

    if (newColumns > newRows.Columns)
        for (unsigned long i=0; i < newRowsResize.Rows; i++)
            newRowsResize.Cells[i].resize(newColumns);

    for (unsigned long i=0; i < newRowsResize.Rows; i++)
        Cells.push_back(newRowsResize.Cells[i]);

    Rows = static_cast<unsigned long>(Cells.size());
    Columns = newColumns;
}
