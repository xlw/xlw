//
//
//                                                        DoubleOrNothing.cpp
//
//
/*
 Copyright (C) 2006 Mark Joshi

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/DoubleOrNothing.h>
#include <xlw/CellMatrix.h>

xlw::DoubleOrNothing::DoubleOrNothing(const CellMatrix& cells, const std::string& identifier)
{
    if (cells.ColumnsInStructure() != 1 || cells.RowsInStructure() != 1)
        THROW_XLW("Multiple values given where one expected for DoubleOrNothing " << identifier);

    if (!cells(0,0).IsEmpty() && !cells(0,0).IsANumber() )
        THROW_XLW("expected a double or nothing, got something else " << identifier);

    Empty = cells(0,0).IsEmpty();

    Value = Empty ? 0.0 : cells(0,0).NumericValue();

}

bool xlw::DoubleOrNothing::IsEmpty() const
{
    return Empty;
}

double xlw::DoubleOrNothing::GetValueOrDefault(double defaultValue) const
{
    return Empty ? defaultValue : Value;
}

