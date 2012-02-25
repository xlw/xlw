//
//
//                        MJCellMatrix.cpp
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2012 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#include <xlw/MJCellMatrix.h>
#include <xlw/XlfException.h>
#include <algorithm>


bool xlw::impl::MJCellValue::IsString() const
{
    return (Type == string) || (Type == wstring);
}

bool xlw::impl::MJCellValue::IsAString() const
{
    return Type == string;
}

bool xlw::impl::MJCellValue::IsAWstring() const
{
    return Type == wstring;
}

bool xlw::impl::MJCellValue::IsANumber() const
{
    return Type == number;
}

bool xlw::impl::MJCellValue::IsBoolean() const
{
    return Type == boolean;
}


bool xlw::impl::MJCellValue::IsError() const
{
    return Type == error;
}

bool xlw::impl::MJCellValue::IsEmpty() const
{
    return Type == empty;
}


xlw::impl::MJCellValue::operator std::string() const
{
    return StringValue();
}

xlw::impl::MJCellValue::operator std::wstring() const
{
    return WstringValue();
}

xlw::impl::MJCellValue::operator bool() const
{
    if (Type != boolean)
        THROW_XLW("non boolean cell asked to be a bool");
    return ValueAsBool;
}

xlw::impl::MJCellValue::operator double() const
{
    if (Type != number)
        THROW_XLW("non number cell asked to be a number");
    return ValueAsNumeric;
}

xlw::impl::MJCellValue::operator unsigned long() const
{
    if (Type != number)
        THROW_XLW("non number cell asked to be a number");
    return static_cast<unsigned long>(ValueAsNumeric);
}


xlw::impl::MJCellValue::MJCellValue(const MJCellValue & value) : Type(value.Type),
	ValueAsNumeric(value.ValueAsNumeric), ValueAsBool(value.ValueAsBool), ValueAsErrorCode(value.ValueAsErrorCode)
{
	if(Type==xlw::impl::MJCellValue::string)
	{
		ValueAsString.reset(new std::string(*value.ValueAsString));
	}
	if(Type==xlw::impl::MJCellValue::wstring)
	{
		ValueAsWstring.reset(new std::wstring(*value.ValueAsWstring));
	}

}

xlw::impl::MJCellValue::MJCellValue(const std::string& value) : Type(xlw::impl::MJCellValue::string),
ValueAsString(new std::string(value)),ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::impl::MJCellValue::MJCellValue(const std::wstring& value) : Type(xlw::impl::MJCellValue::wstring),
ValueAsWstring(new std::wstring(value)), ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{

}


xlw::impl::MJCellValue::MJCellValue(double Number): Type(xlw::impl::MJCellValue::number),
ValueAsNumeric(Number), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::impl::MJCellValue::MJCellValue(int i): Type(xlw::impl::MJCellValue::number),
ValueAsNumeric(i), ValueAsBool(false), ValueAsErrorCode(0)
{

}

xlw::impl::MJCellValue::MJCellValue(unsigned long Code, bool Error): Type(error),
ValueAsNumeric(Code), ValueAsBool(false), ValueAsErrorCode(Code)
{
    if (!Error)
        Type = number;
}

xlw::impl::MJCellValue::MJCellValue(bool TrueFalse)
 : Type(xlw::impl::MJCellValue::boolean),ValueAsNumeric(0.0), ValueAsBool(TrueFalse), ValueAsErrorCode(0)
{
}

xlw::impl::MJCellValue::MJCellValue(): Type(xlw::impl::MJCellValue::empty),
ValueAsNumeric(0.0), ValueAsBool(false), ValueAsErrorCode(0)
{
}

const  std::string & xlw::impl::MJCellValue::StringValue() const
{
    if (Type == string) {
        return *ValueAsString;
    } else if (Type == wstring) {
        ValueAsString.reset(new std::string(ValueAsWstring->begin(), ValueAsWstring->end()));
        return *ValueAsString;
    } else {
        THROW_XLW("non string cell asked to be a string");
    }
}

const std::wstring& xlw::impl::MJCellValue::WstringValue() const
{
    if (Type == wstring) {
        return *ValueAsWstring;
    } else if (Type == string) {
        ValueAsWstring.reset(new std::wstring(ValueAsString->begin(), ValueAsString->end()));
        return *ValueAsWstring;
    } else {
        THROW_XLW("non string cell asked to be a string");
    }
}

double xlw::impl::MJCellValue::NumericValue() const
{

    if (Type != number)
        THROW_XLW("non number cell asked to be a number");
    return ValueAsNumeric;
}

bool xlw::impl::MJCellValue::BooleanValue() const
{

    if (Type != boolean)
        THROW_XLW("non boolean cell asked to be a bool");

    return ValueAsBool;
}

unsigned long xlw::impl::MJCellValue::ErrorValue() const
{
    if (Type != error)
        THROW_XLW("non error cell asked to be an error");

    return ValueAsErrorCode;
}

xlw::impl::MJCellMatrix::MJCellMatrix() : Cells(0), Rows(0), Columns(0)
{
}

xlw::impl::MJCellMatrix::MJCellMatrix(size_t rows, size_t columns)
    : Cells(rows), Rows(rows), Columns(columns)
{
    for (size_t i=0; i < rows; i++)
        Cells[i].resize(columns);
}

const xlw::CellValue& xlw::impl::MJCellMatrix::operator()(size_t i, size_t j) const
{
    return Cells.at(i).at(j);

}
xlw::CellValue& xlw::impl::MJCellMatrix::operator()(size_t i, size_t j)
{
    return Cells.at(i).at(j);
}

size_t xlw::impl::MJCellMatrix::RowsInStructure() const
{
    return Rows;
}
size_t xlw::impl::MJCellMatrix::ColumnsInStructure() const
{
    return Columns;
}

void xlw::impl::MJCellMatrix::PushBottom(const xlw::CellMatrix_pimpl_abstract & newRows)
{
	size_t newColumns = std::max(this->ColumnsInStructure(), newRows.ColumnsInStructure());

	MJCellMatrix temp(this->RowsInStructure()+newRows.RowsInStructure(),newColumns);

	for(size_t i(0); i< RowsInStructure(); ++i)
	{
		for(size_t j(0); j < Cells.at(i).size(); ++j)
		{
			temp(i,j) = Cells.at(i).at(j);
		}
	}

	for(size_t i(0); i< newRows.RowsInStructure(); ++i)
	{
		for(size_t j(0); j < newRows.ColumnsInStructure(); ++j)
		{
			temp(RowsInStructure()+i,j) = newRows(i,j);
		}
	}

	*this = temp;
}


