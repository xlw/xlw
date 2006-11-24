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


#ifndef FUNCTION_MODEL_H
#define FUNCTION_MODEL_H
#include <vector>
#include <string>

class FunctionModel
{
public:

	FunctionModel(std::string ReturnType_, std::string Name, std::string Description, bool Volatile_=false);

	void AddArgument(std::string Type_, std::string Name_, std::string Description_);

	size_t GetNumberArgs() const;

	std::string GetReturnType() const
	{
		return ReturnType;
	}

	std::string GetFunctionName() const
	{	
		return FunctionName;
	}

	std::string GetFunctionDescription() const
	{
		return FunctionDescription;
	}

	std::string GetArgumentReturnType(int i) const
	{	
		return ArgumentTypes.at(i);
	}
	std::string GetArgumentFunctionName(int i) const
	{
		return ArgumentNames.at(i);
	}
	std::string GetArgumentFunctionDescription(int i) const
	{
		return ArgumentDescs.at(i);
	}

	bool GetVolatile() const
	{
		return Volatile;
	}

private:
	std::string ReturnType;
	std::string FunctionName;
	std::string FunctionDescription;
	bool Volatile;

	std::vector<std::string > ArgumentTypes;
	std::vector<std::string > ArgumentNames;
	std::vector<std::string > ArgumentDescs;

};


#endif
