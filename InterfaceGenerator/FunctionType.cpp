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

#include "FunctionType.h"

void CheckAndGetType(char& c, std::string& ConversionString, std::string className)
{
		if (className == "double" )
		{
			c = 'R';
			ConversionString = ".AsDouble";
		}
		else
			if (className == "int" )
			{
				c = 'R';
				ConversionString = ".AsInt";
			}
			else
				if (className == "MyMatrix")
				{
					c = 'P';
					ConversionString = ".AsMatrix";
				}
			else if (className ==  "MyArray"	)
				{
					c = 'R';
					ConversionString = ".AsArray";
				}
					else
						if (className == "CellMatrix"	)
						{
							c = 'P';
							ConversionString = ".AsCellMatrix";
						}
						else
							if (className == "string")
							{
								c='R';
								ConversionString = ".AsString";
							}
							else
								if (className == "std::string")
								{
									c='R';
									ConversionString = ".AsString";
								}
								else 
									if (className == "bool")
									{
										c='R';
										ConversionString = ".AsBool";
									}
									else
										throw("unknown variable type found "+className);
	

	return;
}
std::vector<FunctionDescription> FunctionTyper(std::vector<FunctionModel>& input)
{
	std::vector<FunctionModel>::const_iterator it = input.begin();
	std::vector<FunctionDescription> output;

	while (it != input.end())
	{
		char key;
		std::string conversionString;
		std::string returnType = it->GetReturnType();
		CheckAndGetType(key,conversionString,returnType);
		std::string name = it->GetFunctionName();
		std::string desc = it->GetFunctionDescription();

		std::vector<FunctionArgument> Arguments;
		for (unsigned long i=0; i < it->GetNumberArgs(); i++)
		{
			char thisKey;
			std::string thisConversionString;
			std::string thisType = it->GetArgumentReturnType(i);
			CheckAndGetType(thisKey,thisConversionString,thisType);

			FunctionArgumentType typeDesc(thisType,thisConversionString,thisKey);

			FunctionArgument thisArgument(typeDesc,it->GetArgumentFunctionName(i),it->GetArgumentFunctionDescription(i));
			Arguments.push_back(thisArgument);
		}

		FunctionDescription thisDescription(name,desc,returnType,key,Arguments);
		output.push_back(thisDescription);
		++it;
	}

	return output;
}
