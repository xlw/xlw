//
//
//                                  CellMatrix.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 Narinder S Claire


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

#include <string>
#include <vector>
#include <xlw/MyContainers.h>

namespace xlw {

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
        CellValue(const char* values);
        CellValue(int i);

        CellValue();

        std::string StringValue() const;
        const std::wstring& WstringValue() const;
        const char* CharPtrValue() const;
        double NumericValue() const;
        bool BooleanValue() const;
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
        operator double() const;
        operator unsigned long() const;

        void clear();

    private:
        ValueType Type;

        std::string ValueAsString;
        std::wstring ValueAsWstring;
        double ValueAsNumeric;
        bool ValueAsBool;
        unsigned long ValueAsErrorCode;

    };

    class CellMatrix
    {
    public:

        CellMatrix(size_t rows, size_t columns);
        CellMatrix();
        CellMatrix(double x);
        CellMatrix(std::string x);
        CellMatrix(std::wstring x);
        CellMatrix(const char* x);
        CellMatrix(const MyArray& data);
        CellMatrix(const MyMatrix& data);
        CellMatrix(unsigned long i);
        CellMatrix(int i);

        const CellValue& operator()(size_t i, size_t j) const;
        CellValue& operator()(size_t i, size_t j);

        size_t RowsInStructure() const;
        size_t ColumnsInStructure() const;

        void PushBottom(const CellMatrix& newRows);

    private:

        std::vector<std::vector<CellValue> > Cells;
        size_t Rows;
        size_t Columns;

    };

    CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom);

}

#endif
