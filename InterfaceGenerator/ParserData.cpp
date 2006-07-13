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

#include "ParserData.h"

FunctionArgumentType::FunctionArgumentType(std::string NameIdentifier_,
                          std::string ConversionToMethod_,
                          char EXCELKey_)
                          :
                          NameIdentifier(NameIdentifier_),
                          ConversionToMethod(ConversionToMethod_),
                          EXCELKey(EXCELKey_)
                          {}
                          
     
const std::string& FunctionArgumentType::GetNameIdentifier() const
{
 return NameIdentifier;           
}
           
const std::string& FunctionArgumentType::GetConversionToMethod() const
{
 return ConversionToMethod;
}

FunctionArgumentType FunctionArgument::GetTheType() const
{
 return TheType;
}
char FunctionArgumentType::GetEXCELKey() const
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
						 char ExcelKey_,
                         const std::vector<FunctionArgument>& Arguments_)
                         :
                         FunctionName(FunctionName_),
                         FunctionHelpDescription(FunctionHelpDescription_),
						 ReturnType(ReturnType_),
						 ExcelKey(ExcelKey_),
                         Arguments(Arguments_)
{
}

 char FunctionDescription::GetExcelKey() const
 {
	return ExcelKey;
 }

std::string FunctionDescription::GetReturnType() const
{
	return ReturnType;
}
