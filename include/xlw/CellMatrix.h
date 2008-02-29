//
//
//                                  CellMatrix.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
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
#ifndef CELL_MATRIX_H
#define CELL_MATRIX_H

#include <xlw/port.h>
#include <string>
#include <vector>
#include <xlw/MyContainers.h>
#include <xlw/XlfOper.h>

class CellValue
{

public:
    bool IsAString() const;
    bool IsAWstring() const;
    bool IsANumber() const;
      bool IsBoolean() const;
      bool IsXlfOper() const;
    bool IsError() const;

    bool IsEmpty() const;


    CellValue(const std::string&);
    CellValue(const std::wstring&);
    CellValue(double Number);
    CellValue(unsigned long Code, bool Error=false); //Error = true if you want an error code
    CellValue(bool TrueFalse);
    CellValue(const XlfOper &xlfOper);
    CellValue(const char* values);
    CellValue(int i);

    CellValue();

    //const std::string& StringValue() const;
    std::string StringValue() const;
    const std::wstring& WstringValue() const;
    const char* CharPtrValue() const;
    double NumericValue() const;
    bool BooleanValue() const;
    const XlfOper &XlfOperValue() const;
    unsigned long ErrorValue() const;

    std::string StringValueLowerCase() const;
    std::wstring WstringValueLowerCase() const;

    enum ValueType
    {
        string, wstring, number, boolean, xlfoper, error, empty
    };

    operator std::string() const;
    operator std::wstring() const;
    operator bool() const;
    operator XlfOper() const;
    operator double() const;
    operator unsigned long() const;

    void clear();


private:
    ValueType Type;

    std::string ValueAsString;
    std::wstring ValueAsWstring;
    double ValueAsNumeric;
    bool ValueAsBool;
    XlfOper ValueAsXlfOper;
    unsigned long ValueAsErrorCode;


};

class CellMatrix
{
public:

    CellMatrix(unsigned long rows, unsigned long columns);
    CellMatrix();
    CellMatrix(double x);
    CellMatrix(std::string x);
    CellMatrix(std::wstring x);
    CellMatrix(const char* x);
    CellMatrix(const MyArray& data);
    CellMatrix(const MyMatrix& data);
    CellMatrix(unsigned long i);
    CellMatrix(int i);

    const CellValue& operator()(unsigned long i, unsigned long j) const;
    CellValue& operator()(unsigned long i, unsigned long j);

    unsigned long RowsInStructure() const;
    unsigned long ColumnsInStructure() const;

    void PushBottom(const CellMatrix& newRows);



private:

    std::vector<std::vector<CellValue> > Cells;
    unsigned long Rows;
    unsigned long Columns;

};


CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom);



#endif
