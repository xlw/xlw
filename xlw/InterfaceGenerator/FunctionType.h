/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef FUNCTION_TYPER_H
#define FUNCTION_TYPER_H


#include "TypeRegister.h"
#include <vector>
#include "ParserData.h"
#include "FunctionModel.h"


template<class T>
void CheckAndGetType(std::string& c,
                     std::vector<std::string>& ConversionChain,
                     std::string className)
{
    ConversionChain = TypeRegistry<T>::Instance().GetChain(className);

    size_t i = 0;
    std::string key;
    while (key == "" && i < ConversionChain.size())
    {
		if(!TypeRegistry<T>::Instance().IsTypeRegistered(ConversionChain[i]))
		{
			if(TypeRegistry<T>::Instance().IsOfBaseType(ConversionChain[i]))
			{
				if(i!=ConversionChain.size()-1)
				{
					throw("chain for "+className + " not terminating with parent type " + ConversionChain[i]);
				}
				c="";
				return;
			}
			throw("Unknown type "+ConversionChain[i]);
		}

        typename TypeRegistry<T>::regData  data= TypeRegistry<T>::Instance().GetRegistration(ConversionChain[i]);
        key = data.ExcelKey;
        ++i;
    }


    if (key.size() == 0)
	{

        throw("excel key not given  "+className);
	}

    c = key;

    return;
}


template<class T>
std::vector<FunctionDescription> FunctionTyper(std::vector<FunctionModel>& input)
{
    std::vector<FunctionModel>::const_iterator it = input.begin();
    std::vector<FunctionDescription> output;

    while (it != input.end())
    {
        std::string key;
        std::vector<std::string> conversionString;
        std::string returnType = it->GetReturnType();
        CheckAndGetType<T>(key,conversionString,returnType);
        std::string name = it->GetFunctionName();
        std::string desc = it->GetFunctionDescription();

        std::vector<FunctionArgument> Arguments;
        for (unsigned long i=0; i < it->GetNumberArgs(); i++)
        {
            std::string thisKey;
            std::vector<std::string> thisConversionString;
            std::string thisType = it->GetArgumentReturnType(i);
            CheckAndGetType<T>(thisKey,thisConversionString,thisType);

            FunctionArgumentType typeDesc(thisType,thisConversionString,thisKey);


            FunctionArgument thisArgument(typeDesc,it->GetArgumentFunctionName(i),it->GetArgumentFunctionDescription(i));
            Arguments.push_back(thisArgument);
        }

        FunctionDescription thisDescription(name,desc,returnType,key,Arguments,it->GetVolatile(),it->DoTime(),it->GetThreadsafe(),it->GetHelpID(),
                                            it->GetAsynchronous(), it->GetMacroSheet(), it->GetClusterSafe());
        output.push_back(thisDescription);
        ++it;
    }

    return output;
}



#endif
