//
//
//						ArgList.cpp
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

#include "ArgList.h"
#include <algorithm>
#include <sstream>

namespace
{
	template<class T>
	T maxi(T i, T j)
	{
		return i > j ? i : j;
	}
}

void MakeLowerCase(std::string& input)
{
   std::transform(input.begin(),input.end(),input.begin(),tolower);
}

std::string ConvertToString(double Number)
{
  std::ostringstream os;
  os << Number;
  return os.str();

}

std::string ConvertToString(unsigned long Number)
{
  std::ostringstream os;
  os << Number;
  return os.str();

}


CellMatrix ExtractCells(CellMatrix& cells,
						unsigned long row,
						unsigned long column,
						std::string ErrorId,
						std::string thisName,
						bool nonNumeric)
{
	if (!cells(row,column).IsANumber())
		throw(ErrorId+" "+thisName+" rows and columns expected.");
	if (cells.ColumnsInStructure() <= column+1)
		throw(ErrorId+" "+thisName+" rows and columns expected.");
	if (!cells(row,column+1).IsANumber())
		throw(ErrorId+" "+thisName+" rows and columns expected.");

	unsigned long numberRows = cells(row,column);
	unsigned long numberColumns = cells(row,column+1);

	cells(row,column).clear();
	cells(row,column+1).clear();

	CellMatrix result(numberRows,numberColumns);

	if (numberRows +row+1>cells.RowsInStructure())
		throw(ErrorId+" "+thisName+" insufficient rows in structure");

	if (numberColumns +column>cells.ColumnsInStructure())
		throw(ErrorId+" "+thisName+" insufficient columns in structure");

	for (unsigned long i=0; i < numberRows; i++)
		for (unsigned long j=0; j < numberColumns; j++)
		{
			result(i,j) = cells(row+1+i,column+j);
			cells(row+1+i,column+j).clear();

			if (!result(i,j).IsANumber())
				nonNumeric = true;
		}


	return result;


}


void ArgumentList::add(const std::string& ArgumentName, const std::string& value)
{
	ArgumentType thisOne = string;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);

	std::pair<std::string,std::string> valuePair(ArgumentName,value);
	StringArguments.insert(valuePair);

	RegisterName(ArgumentName, thisOne);
}

void ArgumentList::add(const std::string& ArgumentName, double value)
{
	ArgumentType thisOne = number;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);

	std::pair<std::string,double> valuePair(ArgumentName,value);
	DoubleArguments.insert(valuePair);
	
	RegisterName(ArgumentName, thisOne);
				
}

void ArgumentList::add(const std::string& ArgumentName, const MyArray& value)
{
	ArgumentType thisOne = vector;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);
	ArrayArguments.insert(std::make_pair(ArgumentName,value));
	
	RegisterName(ArgumentName, thisOne);
}

void ArgumentList::add(const std::string& ArgumentName, const MyMatrix& value)
{
	ArgumentType thisOne = matrix;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);
	MatrixArguments.insert(std::make_pair(ArgumentName,value));
	
	RegisterName(ArgumentName, thisOne);
}

void ArgumentList::add(const std::string& ArgumentName, bool value)
{
	ArgumentType thisOne = boolean;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);
	BoolArguments.insert(std::make_pair(ArgumentName,value));
	
	RegisterName(ArgumentName, thisOne);

}

void ArgumentList::add(const std::string& ArgumentName, const CellMatrix& values)
{
	ArgumentType thisOne = cells;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);
	CellArguments.insert(std::make_pair(ArgumentName,values));
	
	RegisterName(ArgumentName, thisOne);

}

   
void ArgumentList::addList(const std::string& ArgumentName, const CellMatrix& values)
{
	ArgumentType thisOne = list;
	std::pair<std::string, ArgumentType> thisPair(ArgumentName,thisOne);
	ArgumentNames.push_back(thisPair);
	ListArguments.insert(std::make_pair(ArgumentName,values));

	
	RegisterName(ArgumentName, thisOne);
}

void ArgumentList::add(const std::string& ArgumentName, const ArgumentList& values)
{
	CellMatrix cellValues(values.AllData());
	addList(ArgumentName,cellValues);
}

ArgumentList::ArgumentList(CellMatrix cells, 
						   std::string ErrorId)
{
	CellValue empty;
	unsigned long rows = cells.RowsInStructure();
	unsigned long columns = cells.ColumnsInStructure();

	if (rows == 0)
		throw(std::string("Argument List requires non empty cell matix ")+ErrorId);

	if (!cells(0,0).IsAString())
		throw(std::string("a structure name must be specified for argument list class ")+ErrorId);
	else
	{
		StructureName = cells(0,0).StringValueLowerCase();
		cells(0,0) = empty;
	}


	{for (unsigned long i=1; i < columns; i++)
		if (!cells(0,i).IsEmpty() )
			throw("An argument list should only have the structure name on the first line: "+StructureName+ " " + ErrorId);
	}

	ErrorId +=" "+StructureName;

	{for (unsigned long i=1; i < rows; i++)
		for (unsigned long j=0; j < columns; j++)
			if (cells(i,j).IsError())
				GenerateThrow("Error Cell passed in ",i,j);}

	unsigned long row=1UL;

	while (row < rows)
	{
		unsigned long rowsDown=1;
		unsigned column = 0;

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
				if (!cells(row,column).IsAString())
					GenerateThrow("data  where name expected.", row, column);

				std::string thisName(cells(row,column).StringValueLowerCase());

				if (thisName =="")
					GenerateThrow("empty name not permissible.", row, column);

				if (rows == row+1)
					GenerateThrow("No space where data expected below name", row, column);

				cells(row,column).clear();
// weird syntax to satisfy VC6
				CellValue* belowPtr = &cells(row+1,column);
				CellValue& cellBelow = *belowPtr;

				if (cellBelow.IsEmpty())
					GenerateThrow("Data expected below name", row, column);

				if (cellBelow.IsANumber())
				{
					add(thisName, cellBelow.NumericValue());

					column++;

					cellBelow=empty;
				}
				else
					if (cellBelow.IsBoolean())
					{
						add(thisName, cellBelow.BooleanValue());

						column++;

						cellBelow=empty; 
					}
					else // ok its a string
					{
						std::string stringVal = cellBelow.StringValueLowerCase();

						if ( (cellBelow.StringValueLowerCase() == "list") || 
							(cellBelow.StringValueLowerCase() == "matrix") ||
							(cellBelow.StringValueLowerCase() == "cells") )
						{
							bool nonNumeric = false;
							CellMatrix extracted(ExtractCells(cells,row+2,column,ErrorId,thisName,nonNumeric));


							if (cellBelow.StringValueLowerCase() == "list")
							{
								ArgumentList value(extracted,ErrorId+":"+thisName);

								addList(thisName, extracted); //note not value

							}

							if (cellBelow.StringValueLowerCase() == "cells")
							{
								add(thisName,extracted);
							}

							
							if (cellBelow.StringValueLowerCase() == "matrix")
							{
								if (nonNumeric)
									throw("Non numerical value in matrix argument :"+thisName+ " "+ErrorId);

								MJMatrix value(extracted.RowsInStructure(),extracted.ColumnsInStructure());

								for (unsigned long i=0; i < extracted.RowsInStructure(); i++)
									for (unsigned long j=0; j < extracted.ColumnsInStructure(); j++)
										ChangingElement(value,i,j) = extracted(i,j);

								add(thisName,value);

							}

							cellBelow = empty;
							rowsDown = maxi(rowsDown,extracted.RowsInStructure()+2);
							column+= extracted.ColumnsInStructure();
						}
						else // ok its an array or boring string
						{
							if (cellBelow.StringValueLowerCase() == "array" 
								||cellBelow.StringValueLowerCase() == "vector" )
							{
								cellBelow.clear();
							
								if (row+2>= rows)
									throw(ErrorId+" data expected below array "+thisName);

								unsigned long size = cells(row+2,column);
								cells(row+2,column).clear();

								if (row+2+size>=rows)
									throw(ErrorId+" more data expected below array "+thisName);


								MyArray theArray(size);

								for (unsigned long i=0; i < size; i++)
								{
									theArray[i] = cells(row+3+i,column);
									cells(row+3+i,column).clear();
								}

								add(thisName,theArray);

								rowsDown = maxi(rowsDown,size+2);
			
								column+=1;
							}
							else
							{
								std::string value = cellBelow.StringValueLowerCase();
								add(thisName,value);
								column++;

								cellBelow=empty; 
							}
						}

					}
			}		

		}	
		row+=rowsDown+1;

	}

    {for (unsigned long i=0; i < rows; i++)
        for (unsigned long j=0; j < columns; j++)
            if (!cells(i,j).IsEmpty())
            {
               GenerateThrow("extraneous data "+ErrorId,i,j);
	}}
}

void ArgumentList::RegisterName(const std::string& ArgumentName, ArgumentType type)
{
	ArgumentNames.push_back(std::make_pair(ArgumentName,type));
	if (!(Names.insert(*ArgumentNames.rbegin()).second) )
                throw("Same argument name used twice "+ArgumentName);

	ArgumentsUsed.insert(std::pair<std::string,bool>(ArgumentName,false));   

}
    
std::string ArgumentList::GetStructureName() const
{
	return StructureName;
}

const std::vector<std::pair<std::string, ArgumentList::ArgumentType> >& ArgumentList::GetArgumentNamesAndTypes() const
{
	return ArgumentNames;
}

void ArgumentList::UseArgumentName(const std::string& ArgumentName)
{
	std::map<std::string,bool>::iterator it= ArgumentsUsed.find(ArgumentName);
    it->second =true;
}
    
std::string ArgumentList::GetStringArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, std::string>::const_iterator it = StringArguments.find(ArgumentName);

    if (it == StringArguments.end())
        throw(StructureName+std::string(" unknown string argument asked for :")+ArgumentName);

	UseArgumentName(ArgumentName);

	return it->second;
    
}

unsigned long ArgumentList::GetULArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, double>::const_iterator it = DoubleArguments.find(ArgumentName);

    if (it == DoubleArguments.end())
        throw(StructureName+std::string(" unknown unsigned long argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return static_cast<unsigned long>(it->second);
}
double ArgumentList::GetDoubleArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, double>::const_iterator it = DoubleArguments.find(ArgumentName);

    if (it == DoubleArguments.end())
        throw(StructureName+std::string(" unknown double argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second; 
}
MyArray ArgumentList::GetArrayArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, MyArray>::const_iterator it = ArrayArguments.find(ArgumentName);

    if (it == ArrayArguments.end())
        throw(StructureName+std::string(" unknown array argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second; 

}

MJMatrix ArgumentList::GetMatrixArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, MJMatrix>::const_iterator it = MatrixArguments.find(ArgumentName);

    if (it == MatrixArguments.end())
        throw(StructureName+std::string(" unknown matrix argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second; 
}
bool ArgumentList::GetBoolArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, bool>::const_iterator it = BoolArguments.find(ArgumentName);

    if (it == BoolArguments.end())
        throw(StructureName+std::string(" unknown bool argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second;

}


ArgumentList ArgumentList::GetArgumentListArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, CellMatrix>::const_iterator it = ListArguments.find(ArgumentName);

    if (it == ListArguments.end())
        throw(StructureName+std::string(" unknown ArgList argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return ArgumentList(it->second,ArgumentName); 
}

CellMatrix ArgumentList::GetCellsArgumentValue(const std::string& ArgumentName_)
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	std::map<std::string, CellMatrix>::const_iterator it = CellArguments.find(ArgumentName);

    if (it == CellArguments.end())
        throw(StructureName+std::string(" unknown Cells argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second; 
}
bool ArgumentList::IsArgumentPresent(const std::string& ArgumentName_) const
{
	std::string ArgumentName(ArgumentName_);
	MakeLowerCase(ArgumentName);
	return (Names.find(ArgumentName) != Names.end());
}

void ArgumentList::CheckAllUsed(const std::string& ErrorId) const
{	
	std::string unusedList;

	for (std::map<std::string,bool>::const_iterator it = ArgumentsUsed.begin();
		it != ArgumentsUsed.end(); it++)
	{
		if (!it->second)
			unusedList+=it->first + std::string(", ");
	}

	if (unusedList !="")
		throw("Unused arguments in "+ErrorId+" "+StructureName+" "+unusedList);

}

void ArgumentList::GenerateThrow(std::string message, unsigned long row, unsigned long column)
{
	throw(StructureName+" "+message+" row:"+ConvertToString(row)+"; column:"+ConvertToString(column)+".");
}

ArgumentList::ArgumentList(std::string name) : StructureName(name)
{
	
}

CellMatrix ArgumentList::AllData() const
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

	{for (std::map<std::string,MyArray>::const_iterator it= ArrayArguments.begin();
			it != ArrayArguments.end(); it++)
	{
		CellMatrix tmp(static_cast<unsigned long>(3+it->second.size()),1);
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("array");
		 tmp(2,0) = static_cast<double>(it->second.size());
		 for (unsigned long i=0; i < it->second.size(); i++)
			 tmp(i+3,0)=it->second[i];
		 results.PushBottom(tmp);
	}}
	
	{for (std::map<std::string,MJMatrix>::const_iterator it= MatrixArguments.begin();
			it != MatrixArguments.end(); it++)
	{
		CellMatrix tmp(3+it->second.rows(),maxi(2UL,it->second.columns()));
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("matrix");
		 tmp(2,0) = static_cast<double>(it->second.rows());
		 tmp(2,1) = static_cast<double>(it->second.columns());
		 for (unsigned long i=0; i < it->second.rows(); i++)
			 for (unsigned long j=0; j < it->second.columns(); j++)
				 tmp(i+3,j)=Element(it->second,i,j);
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
		CellMatrix tmp(3+it->second.RowsInStructure(),maxi(2UL,it->second.ColumnsInStructure()));
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("cells");
		 tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
		 tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
		 for (unsigned long i=0; i < it->second.RowsInStructure(); i++)
			 for (unsigned long j=0; j < it->second.ColumnsInStructure(); j++)
				 tmp(i+3,j)=it->second(i,j);
		 results.PushBottom(tmp);
	}}

	{for (std::map<std::string,CellMatrix>::const_iterator it= ListArguments.begin();
		it != ListArguments.end(); it++)
	{
		CellMatrix tmp(3+it->second.RowsInStructure(),maxi(2UL,it->second.ColumnsInStructure()));
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("list");
		 tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
		 tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
		 for (unsigned long i=0; i < it->second.RowsInStructure(); i++)
			 for (unsigned long j=0; j < it->second.ColumnsInStructure(); j++)
				 tmp(i+3,j)=it->second(i,j);
		 results.PushBottom(tmp);
	}}



	return results;
}


bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								unsigned long& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetULArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								double& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetDoubleArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								MyArray& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetArrayArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								MyMatrix& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetMatrixArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								bool& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetBoolArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								CellMatrix& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetCellsArgumentValue(ArgumentName);
	return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
								ArgumentList& ArgumentValue)
{
	if (!IsArgumentPresent(ArgumentName))
		return false;

	ArgumentValue = GetArgumentListArgumentValue(ArgumentName);
	return true;
}

