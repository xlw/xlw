
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Eric Ehlers
 
 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifdef _MSC_VER
#if _MSC_VER < 1250
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif
#endif
#include "FunctionType.h"
#include "TypeRegister.h"

void CheckAndGetType(std::string& c, 
					 std::vector<std::string>& ConversionChain, 
					 std::string className)
{
	ConversionChain = TypeRegistry::Instance().GetChain(className);

	size_t i = 0;
	std::string key;
	while (key == "" && i < ConversionChain.size())
	{

		TypeRegistry::regData  data= TypeRegistry::Instance().GetRegistration(ConversionChain[i]);
		key = data.ExcelKey;
		++i;
	}

	if (key.size() == 0)
			throw("excel key not given  "+className);

	c = key;

	return;
}

std::vector<FunctionDescription> FunctionTyper(std::vector<FunctionModel>& input)
{
	std::vector<FunctionModel>::const_iterator it = input.begin();
	std::vector<FunctionDescription> output;

	while (it != input.end())
	{
        std::string key;
		std::vector<std::string> conversionString;
		std::string returnType = it->GetReturnType();
		CheckAndGetType(key,conversionString,returnType);
		std::string name = it->GetFunctionName();
		std::string desc = it->GetFunctionDescription();

		std::vector<FunctionArgument> Arguments;
		for (unsigned long i=0; i < it->GetNumberArgs(); i++)
		{
			std::string thisKey;
			std::vector<std::string> thisConversionString;
			std::string thisType = it->GetArgumentReturnType(i);
			CheckAndGetType(thisKey,thisConversionString,thisType);

			FunctionArgumentType typeDesc(thisType,thisConversionString,thisKey);


			FunctionArgument thisArgument(typeDesc,it->GetArgumentFunctionName(i),it->GetArgumentFunctionDescription(i));
			Arguments.push_back(thisArgument);
		}

		FunctionDescription thisDescription(name,desc,returnType,key,Arguments,it->GetVolatile(),it->DoTime(),it->GetThreadsafe());
		output.push_back(thisDescription);
		++it;
	}

	return output;
}
