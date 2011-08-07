
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 Narinder Claire

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
#endif
#endif
#include "ParserData.h"
#include <vector>

FunctionArgumentType::FunctionArgumentType(std::string NameIdentifier_,
                          const std::vector<std::string>& ConversionChain_,
                          const std::string& EXCELKey_)
                          :
                          NameIdentifier(NameIdentifier_),
                          ConversionChain(ConversionChain_),
                          EXCELKey(EXCELKey_)
                          {}


const std::string& FunctionArgumentType::GetNameIdentifier() const
{
 return NameIdentifier;
}

const std::vector<std::string>& FunctionArgumentType::GetConversionChain() const
{
 return ConversionChain;
}

FunctionArgumentType FunctionArgument::GetTheType() const
{
 return TheType;
}
const std::string& FunctionArgumentType::GetEXCELKey() const
{
    return EXCELKey;
}

std::string FunctionArgument::GetArgumentName() const
{
 return ArgumentName;
}

std::string FunctionArgument::GetArgumentDescription() const
{
 return ArgumentDescription;
}

FunctionArgument::FunctionArgument(const FunctionArgumentType& TheType_,
                        std::string ArgumentName_,
                        std::string ArgumentDescription_)
                        :
                        TheType(TheType_),
                        ArgumentName(ArgumentName_),
                        ArgumentDescription(ArgumentDescription_)
{
}

std::string FunctionDescription::GetFunctionName() const
{
return FunctionName;
}

std::string FunctionDescription::GetDisplayName() const
{
return DisplayName;
}


void FunctionDescription::setFunctionName(const std::string &newName)
{
 FunctionName = newName;
}


std::string FunctionDescription::GetFunctionDescription() const
{
return FunctionHelpDescription;
}

const FunctionArgument& FunctionDescription::GetArgument(
                                  unsigned long ArgumentNumber) const
{
   return Arguments.at(ArgumentNumber);
}

unsigned long FunctionDescription::NumberOfArguments() const
{
   return static_cast<unsigned long>(Arguments.size());
}
FunctionDescription::FunctionDescription(std::string FunctionName_,
                         std::string FunctionHelpDescription_,
                         std::string ReturnType_,
                         const std::string& ExcelKey_,
                         const std::vector<FunctionArgument>& Arguments_,
                         bool Volatile_,
                         bool Time_,
                         bool Threadsafe_,
                         std::string helpID_,
                         bool Asynchronous_,
                         bool MacroSheet_,
                         bool ClusterSafe_)
                         :
                         FunctionName(FunctionName_),
                         DisplayName(FunctionName_),
                         FunctionHelpDescription(FunctionHelpDescription_),
                         ReturnType(ReturnType_),
                         ExcelKey(ExcelKey_),
                         helpID(helpID_),
                         Arguments(Arguments_),
                         Volatile(Volatile_),
                         Time(Time_),
                         Threadsafe(Threadsafe_),
                         Asynchronous(Asynchronous_),
                         MacroSheet(MacroSheet_),
                         ClusterSafe(ClusterSafe_)
{
}

 std::string FunctionDescription::GetExcelKey() const
 {
    return ExcelKey;
 }

std::string FunctionDescription::GetReturnType() const
{
    return ReturnType;
}

bool FunctionDescription::GetVolatile() const
{
    return  Volatile;
}

bool FunctionDescription::DoTime() const
{
    return  Time;
}

bool FunctionDescription::GetThreadsafe() const
{
    return  Threadsafe;
}

std::string FunctionDescription::GetHelpID() const
{
    return helpID;
}
bool FunctionDescription::GetAsynchronous() const
{
    return Asynchronous;
}

bool FunctionDescription::GetMacroSheet() const
{
    return MacroSheet;
}

bool FunctionDescription::GetClusterSafe() const
{
    return ClusterSafe;
}

#include<iostream>
void FunctionDescription::Transit(const std::vector<FunctionDescription> &source, 
			 std::vector<FunctionDescription> & destination)
{
	if(source.size()!=destination.size())
	{
		throw("number of managed functions and native wrappers not the same");
	}
	for(size_t i(0); i <destination.size(); ++i)
	{
		destination[i].Asynchronous             = source[i].Asynchronous;
		destination[i].ClusterSafe              = source[i].ClusterSafe  ;
		destination[i].DisplayName              = source[i].DisplayName  ;
		destination[i].FunctionHelpDescription  = source[i].FunctionHelpDescription  ;
		destination[i].helpID                   = source[i].helpID  ;
		destination[i].MacroSheet               = source[i].MacroSheet  ;
		destination[i].Threadsafe               = source[i].Threadsafe  ;
		destination[i].Time                     = source[i].Time  ;
		destination[i].Volatile                 = source[i].Volatile  ;

		if(destination[i].FunctionName != source[i].FunctionName)
		{
			std::cout << destination[i].FunctionName << " : " << source[i].FunctionName << "\n";
			throw("unmanaged wrappers must be in same order as manged function");

		}

	}

}