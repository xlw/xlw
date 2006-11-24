//
//	
//									XlFunctionRegistriation.cpp
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
#include "pragmas.h"
#include "XlFunctionRegistration.h"
#include "xlfFuncDesc.h"
#include "xlfArgDescList.h"

using namespace XLRegistration;

XLFunctionRegistrationData::XLFunctionRegistrationData(const std::string& FunctionName_,
                     const std::string& ExcelFunctionName_,
                     const std::string& FunctionDescription_,
                     const std::string& Library_,
                     const Arg Arguments[],
                     const char* ArgumentTypes_,
					 bool Volatile_)
	:				FunctionName(FunctionName_),
                     ExcelFunctionName(ExcelFunctionName_),
                     FunctionDescription(FunctionDescription_),
                     Library(Library_),
                     ArgumentTypes(ArgumentTypes_),
					 Volatile(Volatile_)
{

	NoOfArguments =static_cast<int>(ArgumentTypes.size());

	ArgumentNames.reserve(NoOfArguments);
	ArgumentDescriptions.reserve(NoOfArguments);

	for (int i=0; i < NoOfArguments; i++)
	{
		ArgumentNames.push_back(Arguments[i].ArgumentName);
		ArgumentDescriptions.push_back(Arguments[i].ArgumentDescription);
	}
}

std::string XLFunctionRegistrationData::GetFunctionName() const
{
	return FunctionName;
}
std::string XLFunctionRegistrationData::GetExcelFunctionName() const
{
	return ExcelFunctionName;
}
std::string XLFunctionRegistrationData::GetFunctionDescription() const
{
	return FunctionDescription;
}


std::string XLFunctionRegistrationData::GetLibrary() const
{
	return Library;
}

int XLFunctionRegistrationData::GetNoOfArguments() const{ 
	return NoOfArguments;
}

std::vector<std::string> XLFunctionRegistrationData::GetArgumentNames() const
{
	return ArgumentNames;
}

std::vector<std::string> XLFunctionRegistrationData::GetArgumentDescriptions() const
{ 
	return ArgumentDescriptions;
}

std::string XLFunctionRegistrationData::GetArgumentTypes() const
{ 
	return ArgumentTypes;
}


XLFunctionRegistrationHelper::XLFunctionRegistrationHelper(const std::string& FunctionName,
                     const std::string& ExcelFunctionName,
                     const std::string& FunctionDescription,
                     const std::string& Library,
                     const Arg Args[],
                     const char* Types,
					 bool Volatile)
{
	XLFunctionRegistrationData tmp(FunctionName, 
																ExcelFunctionName, 
																FunctionDescription, 
																Library, 
																Args, 
																Types,
																Volatile);

	ExcelFunctionRegistrationRegistry::Instance().AddFunction(tmp);
}

ExcelFunctionRegistrationRegistry& ExcelFunctionRegistrationRegistry::Instance()
{
	static ExcelFunctionRegistrationRegistry SingleInstance;
	return SingleInstance;
}

void ExcelFunctionRegistrationRegistry::DoTheRegistrations() const
{
	for (std::list<XLFunctionRegistrationData>::const_iterator it = RegistrationData.begin(); it !=  RegistrationData.end(); ++it)
	{
		XlfFuncDesc::RecalcPolicy policy = it->GetVolatile() ? XlfFuncDesc::Volatile : XlfFuncDesc::NotVolatile;
		 XlfFuncDesc xlFunction(it->GetFunctionName(), 
													it->GetExcelFunctionName(), 
													it->GetFunctionDescription(), 
													it->GetLibrary(),
													policy);
		XlfArgDescList xlFunctionArgs;

		for (int i=0; i < it->GetNoOfArguments(); ++i)
		{
				XlfArgDesc ThisArgumentDescription(it->GetArgumentNames()[i],
																				it->GetArgumentDescriptions()[i],
																				it->GetArgumentTypes()[i]);
				xlFunctionArgs + ThisArgumentDescription; 
																							//+ is a push_back operation
		}

		 xlFunction.SetArguments(xlFunctionArgs);
		 xlFunction.Register();
	}

}
void ExcelFunctionRegistrationRegistry::AddFunction(const XLFunctionRegistrationData& data)
{
	RegistrationData.push_back(data);
}

ExcelFunctionRegistrationRegistry::ExcelFunctionRegistrationRegistry()
{
}

ExcelFunctionRegistrationRegistry::ExcelFunctionRegistrationRegistry(const ExcelFunctionRegistrationRegistry& original)
{ // declared to make private
}
