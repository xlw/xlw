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


	for (unsigned long i=1; i < columns; i++)
		if (!cells(0,i).IsEmpty() )
			throw("An argument list should only have the structure name on the first line: "+StructureName+ " " + ErrorId);

	ErrorId +=" "+StructureName;

	for (unsigned long i=1; i < rows; i++)
		for (unsigned long j=0; j < columns; j++)
			if (cells(i,j).IsError())
				GenerateThrow("Error Cell passed in ",i,j);

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

				CellValue& cellBelow(cells(row+1,column));

				if (cellBelow.IsEmpty())
					GenerateThrow("Data expected below name", row, column);

				if (cellBelow.IsANumber())
				{
					double value = cellBelow.NumericValue();

					ArgumentType thisOne = number;

					std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
					ArgumentNames.push_back(thisPair);

					std::pair<std::string,double> valuePair(thisName,value);

					DoubleArguments.insert(valuePair);

					column++;

					cellBelow=empty;
				}
				else
					if (cellBelow.IsBoolean())
					{

						bool value = cellBelow.BooleanValue();

						ArgumentType thisOne = boolean;

						std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
						ArgumentNames.push_back(thisPair);

						std::pair<std::string,bool> valuePair(thisName,value);

						BoolArguments.insert(valuePair);

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

								ArgumentType thisOne = list;

								std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
								ArgumentNames.push_back(thisPair);

								std::pair<std::string,ArgumentList> valuePair(thisName,value);

								ListArguments.insert(valuePair);

							}

							if (cellBelow.StringValueLowerCase() == "cells")
							{
								ArgumentType thisOne = ArgumentList::cells;

								std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
								ArgumentNames.push_back(thisPair);

								std::pair<std::string,CellMatrix> valuePair(thisName,extracted);

								CellArguments.insert(valuePair);
							}

							
							if (cellBelow.StringValueLowerCase() == "matrix")
							{
								if (nonNumeric)
									throw("Non numerical value in matrix argument :"+thisName+ " "+ErrorId);

								ArgumentType thisOne = matrix;

								MJMatrix value(extracted.RowsInStructure(),extracted.ColumnsInStructure());

								for (unsigned long i=0; i < extracted.RowsInStructure(); i++)
									for (unsigned long j=0; j < extracted.ColumnsInStructure(); j++)
										value(i,j) = extracted(i,j);

								std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
								ArgumentNames.push_back(thisPair);

								std::pair<std::string,MJMatrix> valuePair(thisName,value);

								MatrixArguments.insert(valuePair);
							}

							cellBelow = empty;
							rowsDown = std::max(rowsDown,extracted.RowsInStructure()+2);
							column+= extracted.ColumnsInStructure();
						}
						else // ok its an array or boring string
						{
							if (cellBelow.StringValueLowerCase() == "array" 
								||cellBelow.StringValueLowerCase() == "vector" )
							{
								cellBelow.clear();
								ArgumentType thisOne = vector;

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



								std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
								ArgumentNames.push_back(thisPair);

								std::pair<std::string,MyArray> valuePair(thisName,theArray);

								ArrayArguments.insert(valuePair);
								rowsDown = std::max(rowsDown,size+2);
			
								column+=1;
							}
							else
							{
								std::string value = cellBelow.StringValueLowerCase();

								ArgumentType thisOne = string;

								std::pair<std::string, ArgumentType> thisPair(thisName,thisOne);
								ArgumentNames.push_back(thisPair);

								std::pair<std::string,std::string> valuePair(thisName,value);

								StringArguments.insert(valuePair);

								column++;

								cellBelow=empty; 
							}
						}

					}
			}		

		}	
		row+=rowsDown+1;

	}

    for (unsigned long i=0; i < rows; i++)
        for (unsigned long j=0; j < columns; j++)
            if (!cells(i,j).IsEmpty())
            {
               GenerateThrow("extraneous data "+ErrorId,i,j);
            }

   for (unsigned long i=0; i < ArgumentNames.size(); i++)
        {
            if (!(Names.insert(ArgumentNames[i]).second) )
                throw("Same argument name used twice "+ArgumentNames[i].first+" "+ErrorId);

            ArgumentsUsed.insert(std::pair<std::string,bool>(ArgumentNames[i].first,false));   
        }
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
	std::map<std::string, ArgumentList>::const_iterator it = ListArguments.find(ArgumentName);

    if (it == ListArguments.end())
        throw(StructureName+std::string(" unknown ArgList argument asked for :")+ArgumentName);

    UseArgumentName(ArgumentName);
	return it->second; 
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


CellMatrix ArgumentList::AllData() const
{
	CellMatrix results(1,1);
	results(0,0)= StructureName;
	   
	for (std::map<std::string,double>::const_iterator it= DoubleArguments.begin();
			it != DoubleArguments.end(); it++)
	{
		 CellMatrix tmp(2,1);
		 tmp(0,0) = it->first;
		 tmp(1,0) = it->second;
		 results.PushBottom(tmp);
	}

	for (std::map<std::string,MyArray>::const_iterator it= ArrayArguments.begin();
			it != ArrayArguments.end(); it++)
	{
		CellMatrix tmp(static_cast<unsigned long>(3+it->second.size()),1);
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("array");
		 tmp(2,0) = static_cast<double>(it->second.size());
		 for (unsigned long i=0; i < it->second.size(); i++)
			 tmp(i+3,0)=it->second[i];
		 results.PushBottom(tmp);
	}
	
	for (std::map<std::string,MJMatrix>::const_iterator it= MatrixArguments.begin();
			it != MatrixArguments.end(); it++)
	{
		CellMatrix tmp(3+it->second.rows(),std::max(2UL,it->second.columns()));
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("matrix");
		 tmp(2,0) = static_cast<double>(it->second.rows());
		 tmp(2,1) = static_cast<double>(it->second.columns());
		 for (unsigned long i=0; i < it->second.rows(); i++)
			 for (unsigned long j=0; j < it->second.columns(); j++)
				 tmp(i+3,j)=it->second(i,j);
		 results.PushBottom(tmp);
	}

	for (std::map<std::string,std::string>::const_iterator it= StringArguments.begin();
			it != StringArguments.end(); it++)
	{
		 CellMatrix tmp(2,1);
		 tmp(0,0) = it->first;
		 tmp(1,0) = it->second;
		 results.PushBottom(tmp);
	}
	for (std::map<std::string,bool>::const_iterator it= BoolArguments.begin();
			it != BoolArguments.end(); it++)
	{
		 CellMatrix tmp(2,1);
		 tmp(0,0) = it->first;
		 tmp(1,0) = it->second;
		 results.PushBottom(tmp);
	}
	for (std::map<std::string,CellMatrix>::const_iterator it= CellArguments.begin();
			it != CellArguments.end(); it++)
	{
		CellMatrix tmp(3+it->second.RowsInStructure(),std::max(2UL,it->second.ColumnsInStructure()));
		 tmp(0,0) = it->first;
		 tmp(1,0) = std::string("cells");
		 tmp(2,0) = static_cast<double>(it->second.RowsInStructure());
		 tmp(2,1) = static_cast<double>(it->second.ColumnsInStructure());
		 for (unsigned long i=0; i < it->second.RowsInStructure(); i++)
			 for (unsigned long j=0; j < it->second.ColumnsInStructure(); j++)
				 tmp(i+3,j)=it->second(i,j);
		 results.PushBottom(tmp);
	}

	for (std::map<std::string,ArgumentList>::const_iterator it= ListArguments.begin();
		it != ListArguments.end(); it++)
	{
		CellMatrix cells(it->second.AllData());

		CellMatrix tmp(3,2);
		tmp(0,0) = it->first;
		tmp(1,0) = std::string("list");
		tmp(2,0) = static_cast<double>(cells.RowsInStructure());
		tmp(2,1) = static_cast<double>(cells.ColumnsInStructure());
		tmp.PushBottom(cells);

		results.PushBottom(tmp);
	}

	return results;
}

  
