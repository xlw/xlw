//
//
//                        ArgList.cpp
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/ArgList.h>
#include <sstream>
#include <xlw/PascalStringConversions.h>
#include <algorithm>

namespace
{
    xlw::CellMatrix ExtractCells(xlw::CellMatrix& cells,
                            size_t row,
                            size_t column,
                            std::string ErrorId,
                            std::string thisName,
                            bool& nonNumeric)
    {
        if (!cells(row,column).IsANumber())
            THROW_XLW(ErrorId << " " << thisName << " rows and columns expected.");
        if (cells.ColumnsInStructure() <= column+1)
            THROW_XLW(ErrorId << " " << thisName << " rows and columns expected.");
        if (!cells(row,column+1).IsANumber())
            THROW_XLW(ErrorId << " " << thisName << " rows and columns expected.");

        unsigned long numberRows_UL = cells(row,column);
        unsigned long numberColumns_UL = cells(row,column+1);

        size_t numberRows = static_cast<size_t>(numberRows_UL);
        size_t numberColumns = static_cast<size_t>(numberColumns_UL);

        cells(row,column).clear();
        cells(row,column+1).clear();

        xlw::CellMatrix result(numberRows,numberColumns);

        if (numberRows +row+1>cells.RowsInStructure())
            throw(ErrorId+" "+thisName+" insufficient rows in structure");

        if (numberColumns +column>cells.ColumnsInStructure())
            throw(ErrorId+" "+thisName+" insufficient columns in structure");

        for (size_t i=0; i < numberRows; i++)
            for (size_t j=0; j < numberColumns; j++)
            {
                result(i,j) = cells(row+1+i,column+j);
                cells(row+1+i,column+j).clear();

                if (!result(i,j).IsANumber())
                    nonNumeric = true;
            }

        return result;
    }


}

namespace xlw
{
    template<class TYPE>
    void ArgumentList::addInternal(const std::string& ArgumentName, const TYPE& value, std::map<std::string,TYPE>& typeMap, ArgumentType type)
    {
        std::pair<std::string, TYPE> valuePair(ArgumentName,value);
        typeMap.insert(valuePair);

        RegisterName(ArgumentName, type);
    }

    template<class TYPE>
    const TYPE& ArgumentList::GetArgumentValueInternal(std::string ArgumentName, std::map<std::string, TYPE>& typeMap)
    {
        StringUtilities::makeLower(ArgumentName);
        typename std::map<std::string, TYPE>::const_iterator it = typeMap.find(ArgumentName);

        if (it == typeMap.end())
            THROW_XLW(StructureName << " unknown string argument asked for :" << ArgumentName);

        UseArgumentName(ArgumentName);

        return it->second;
    }
}

void xlw::ArgumentList::add(const std::string& ArgumentName, const char * value)
{
	add(ArgumentName, std::string(value));
}

void xlw::ArgumentList::add(const std::string& ArgumentName, const std::string& value)
{
    addInternal(ArgumentName, value, StringArguments, string);
}

void xlw::ArgumentList::add(const std::string& ArgumentName, double value)
{
    addInternal(ArgumentName, value, DoubleArguments, number);
}

void xlw::ArgumentList::add(const std::string& ArgumentName, bool value)
{
    addInternal(ArgumentName, value, BoolArguments, boolean);
}

void xlw::ArgumentList::add(const std::string& ArgumentName, const CellMatrix& values)
{
    addInternal(ArgumentName, values, CellArguments, cells);
}

void xlw::ArgumentList::addList(const std::string& ArgumentName, const CellMatrix& values)
{
    addInternal(ArgumentName, values, ListArguments, list);
}

void xlw::ArgumentList::addArray(const std::string& ArgumentName, const CellMatrix& values)
{
    addInternal(ArgumentName, values, ArrayArguments, vector);
}

void xlw::ArgumentList::addMatrix(const std::string& ArgumentName, const CellMatrix& values)
{
    addInternal(ArgumentName, values, MatrixArguments, matrix);
}

void xlw::ArgumentList::add(const std::string& ArgumentName, const ArgumentList& values)
{
    CellMatrix cellValues(values.AllData());
    addInternal(ArgumentName, cellValues, ListArguments, list);
}

xlw::ArgumentList::ArgumentList(CellMatrix cells, std::string ErrorId)
{

    size_t rows = cells.RowsInStructure();
    size_t columns = cells.ColumnsInStructure();

    if (rows == 0)
        THROW_XLW("Argument List requires non empty cell matix " << ErrorId);

    //if (!cells(0,0).IsAString())
    if (!cells(0,0).IsAString() && !cells(0,0).IsAWstring())//FIXME
        THROW_XLW("a structure name must be specified for argument list class " << ErrorId);
    else
    {
        StructureName = StringUtilities::toLower(cells(0,0).StringValue());
		cells(0,0).clear();
    }


    {for (size_t i=1; i < columns; i++)
        if (!cells(0,i).IsEmpty() )
            THROW_XLW("An argument list should only have the structure name on the first line: " << StructureName+ " " << ErrorId);
    }

    ErrorId +=" "+StructureName;

    {for (size_t i=1; i < rows; i++)
        for (size_t j=0; j < columns; j++)
            if (cells(i,j).IsError())
                GenerateThrow("Error Cell passed in ",i,j);}

    size_t row=1UL;

    while (row < rows)
    {
        size_t rowsDown=1;
        size_t column = 0;

        while (column < columns)
        {
            if (cells(row,column).IsEmpty())
            {
                // check nothing else in row
                while (column< columns)
                {
                    if (!cells(row,column).IsEmpty())
                        GenerateThrow("data or value where unexpected.",row, column);

                    ++column;
                }
            }
            else // we have data
            {
                //if (!cells(row,column).IsAString())
                if (!cells(row,column).IsAString() && !cells(row,column).IsAWstring())//FIXME
                    GenerateThrow("data  where name expected.", row, column);

                std::string thisName(StringUtilities::toLower(cells(row,column).StringValue()));

                if (thisName =="")
                    GenerateThrow("empty name not permissible.", row, column);

                if (rows == row+1)
                    GenerateThrow("No space where data expected below name", row, column);

                cells(row,column).clear();
                // weird syntax to satisfy VC6
                //CellValue* belowPtr = &cells(row+1,column);
                //CellValue& cellBelow = *belowPtr;
                CellValue& cellBelow = cells(row+1,column);

                if (cellBelow.IsEmpty())
                    GenerateThrow("Data expected below name", row, column);

                if (cellBelow.IsANumber())
                {
                    add(thisName, cellBelow.NumericValue());

                    column++;

					cellBelow.clear();
                }
                else
                    if (cellBelow.IsBoolean())
                    {
                        add(thisName, cellBelow.BooleanValue());

                        column++;

						cellBelow.clear();
                    }
                    else // ok it's a string
                    {
                        std::string stringVal = StringUtilities::toLower(cellBelow.StringValue());

                        if ( (stringVal == "list") ||
                            (stringVal == "matrix") ||
                            (stringVal == "cells") )
                        {
                            bool nonNumeric = false;
                            CellMatrix extracted(ExtractCells(cells,row+2,column,ErrorId,thisName,nonNumeric));


                            if (stringVal == "list")
                            {
                                ArgumentList value(extracted,ErrorId+":"+thisName);

                                addList(thisName, extracted); //note not value

                            }

                            if (stringVal == "cells")
                            {
                                add(thisName,extracted);
                            }


                            if (stringVal == "matrix")
                            {
                                if (nonNumeric)
                                    THROW_XLW("Non numerical value in matrix argument :" << thisName <<  " " << ErrorId);

                                addInternal(thisName, extracted, MatrixArguments, matrix);
                            }

                            cellBelow.clear();
                            rowsDown = std::max(rowsDown,extracted.RowsInStructure()+2);
                            column+= extracted.ColumnsInStructure();
                        }
                        else // ok it's an array or boring string
                        {
                            if (stringVal == "array"
                                ||stringVal == "vector" )
                            {
                                cellBelow.clear();

                                if (row+2>= rows)
                                    THROW_XLW(ErrorId << " data expected below array " << thisName);

                                size_t size = static_cast<size_t>((unsigned long)cells(row+2,column));
                                cells(row+2,column).clear();

                                if (row+2+size>=rows)
                                    THROW_XLW(ErrorId << " more data expected below array " << thisName);

                                CellMatrix theArray(size, 1);

                                for (size_t i=0; i < size; i++)
                                {
                                    CellValue& theValue(cells(row+3+i,column));
                                    if(theValue.IsANumber())
                                    {
                                        theArray(i, 0) = theValue;
                                        theValue.clear();
                                    }
                                    else
                                    {
                                        THROW_XLW("Non numerical value in array argument :" << thisName+ " " << ErrorId);
                                    }
                                }

                                addInternal(thisName, theArray, ArrayArguments, vector);

                                rowsDown = std::max(rowsDown,size+2);

                                column+=1;
                            }
                            else
                            {
                                std::string value = stringVal;
                                add(thisName,value);
                                column++;

								cellBelow.clear();
                            }
                        }

                    }
            }

        }
        row+=rowsDown+1;

    }

    {for (size_t i=0; i < rows; i++)
        for (size_t j=0; j < columns; j++)
            if (!cells(i,j).IsEmpty())
            {
               GenerateThrow("extraneous data "+ErrorId,i,j);
    }}
}

void xlw::ArgumentList::RegisterName(const std::string& ArgumentName, ArgumentType type)
{
    ArgumentNames.push_back(std::make_pair(ArgumentName,type));
    if (!(Names.insert(*ArgumentNames.rbegin()).second) )
                THROW_XLW("Same argument name used twice " << ArgumentName);

    ArgumentsUsed.insert(std::pair<std::string,bool>(ArgumentName,false));

}

std::string xlw::ArgumentList::GetStructureName() const
{
    return StructureName;
}

const std::vector<std::pair<std::string, xlw::ArgumentList::ArgumentType> >& xlw::ArgumentList::GetArgumentNamesAndTypes() const
{
    return ArgumentNames;
}

void xlw::ArgumentList::UseArgumentName(const std::string& ArgumentName)
{
    std::map<std::string,bool>::iterator it= ArgumentsUsed.find(ArgumentName);
    it->second =true;
}

std::string xlw::ArgumentList::GetStringArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, StringArguments);
}

unsigned long xlw::ArgumentList::GetULArgumentValue(const std::string& ArgumentName)
{
    return static_cast<unsigned long>(GetArgumentValueInternal(ArgumentName, DoubleArguments));
}

double xlw::ArgumentList::GetDoubleArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, DoubleArguments);
}

const xlw::CellMatrix& xlw::ArgumentList::GetArrayArgumentValueInternal(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, ArrayArguments);
}

const xlw::CellMatrix& xlw::ArgumentList::GetMatrixArgumentValueInternal(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, MatrixArguments);
}

bool xlw::ArgumentList::GetBoolArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, BoolArguments);
}

xlw::ArgumentList xlw::ArgumentList::GetArgumentListArgumentValue(const std::string& ArgumentName)
{
    return ArgumentList(GetArgumentValueInternal(ArgumentName, ListArguments),ArgumentName);
}

xlw::CellMatrix xlw::ArgumentList::GetCellsArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, CellArguments);
}

bool xlw::ArgumentList::IsArgumentPresent(const std::string& ArgumentName_) const
{
    return (Names.find(StringUtilities::toLower(ArgumentName_)) != Names.end());
}

void xlw::ArgumentList::CheckAllUsed(const std::string& ErrorId) const
{
    std::string unusedList;

    for (std::map<std::string,bool>::const_iterator it = ArgumentsUsed.begin();
        it != ArgumentsUsed.end(); it++)
    {
        if (!it->second)
            unusedList+=it->first + std::string(", ");
    }

    if (unusedList !="")
        THROW_XLW("Unused arguments in " << ErrorId << " " << StructureName << " " << unusedList);

}

void xlw::ArgumentList::GenerateThrow(std::string message, size_t row, size_t column)
{
    THROW_XLW(StructureName << " " << message << " row:" << static_cast<unsigned long>(row) << "; column:" << static_cast<unsigned long>(column));
}

xlw::ArgumentList::ArgumentList(std::string name) : StructureName(name)
{

}

xlw::CellMatrix xlw::ArgumentList::AllData() const
{
    CellMatrix results(1,1);
    results(0,0)= StructureName;

    {for (std::map<std::string,double>::const_iterator it= DoubleArguments.begin();
            it != DoubleArguments.end(); it++)
    {
         CellMatrix tmp(2,1);
         tmp(0,0) = it->first;
         tmp(1,0) = it->second;
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,CellMatrix>::const_iterator it= ArrayArguments.begin();
            it != ArrayArguments.end(); it++)
    {
         CellMatrix tmp(3+it->second.RowsInStructure(),1);
         tmp(0,0) = it->first;
         tmp(1,0) = std::string("array");
         tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
         for (size_t i=0; i < it->second.RowsInStructure(); i++)
             tmp(i+3,0)=it->second(i, 0);
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,CellMatrix>::const_iterator it= MatrixArguments.begin();
            it != MatrixArguments.end(); it++)
    {
         CellMatrix tmp(3+it->second.RowsInStructure(),std::max(size_t(2), it->second.ColumnsInStructure()));
         tmp(0,0) = it->first;
         tmp(1,0) = std::string("matrix");
         tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
         tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
         for (size_t i=0; i < it->second.RowsInStructure(); i++)
             for (size_t j=0; j < it->second.ColumnsInStructure(); j++)
                 tmp(i+3,j)=it->second(i,j);
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,std::string>::const_iterator it= StringArguments.begin();
            it != StringArguments.end(); it++)
    {
         CellMatrix tmp(2,1);
         tmp(0,0) = it->first;
         tmp(1,0) = it->second;
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,bool>::const_iterator it= BoolArguments.begin();
            it != BoolArguments.end(); it++)
    {
         CellMatrix tmp(2,1);
         tmp(0,0) = it->first;
         tmp(1,0) = it->second;
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,CellMatrix>::const_iterator it= CellArguments.begin();
            it != CellArguments.end(); it++)
    {
        CellMatrix tmp(3+it->second.RowsInStructure(),std::max(size_t(2),it->second.ColumnsInStructure()));
         tmp(0,0) = it->first;
         tmp(1,0) = std::string("cells");
         tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
         tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
         for (size_t i=0; i < it->second.RowsInStructure(); i++)
             for (size_t j=0; j < it->second.ColumnsInStructure(); j++)
                 tmp(i+3,j)=it->second(i,j);
         results.PushBottom(tmp);
    }}

    {for (std::map<std::string,CellMatrix>::const_iterator it= ListArguments.begin();
        it != ListArguments.end(); it++)
    {
        CellMatrix tmp(3+it->second.RowsInStructure(),std::max(size_t(2),it->second.ColumnsInStructure()));
         tmp(0,0) = it->first;
         tmp(1,0) = std::string("list");
         tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
         tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
         for (size_t i=0; i < it->second.RowsInStructure(); i++)
             for (size_t j=0; j < it->second.ColumnsInStructure(); j++)
                 tmp(i+3,j)=it->second(i,j);
         results.PushBottom(tmp);
    }}



    return results;
}


bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                unsigned long& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetULArgumentValue(ArgumentName);
    return true;
}

bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                double& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetDoubleArgumentValue(ArgumentName);
    return true;
}

bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                bool& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetBoolArgumentValue(ArgumentName);
    return true;
}

bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                CellMatrix& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetCellsArgumentValue(ArgumentName);
    return true;
}

bool xlw::ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                ArgumentList& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetArgumentListArgumentValue(ArgumentName);
    return true;
}
