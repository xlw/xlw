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
#if !defined(REGISTER_XL_FUNCTION_H)
#define REGISTER_XL_FUNCTION_H


#include <string>
#include <vector>
#include <list>

namespace XLRegistration
{

struct Arg { const char * ArgumentName; const char * ArgumentDescription; };

class XLFunctionRegistrationData
{
public:
  	XLFunctionRegistrationData(const std::string& FunctionName_,
                     const std::string& ExcelFunctionName_,
                     const std::string& FunctionDescription_,
                     const std::string& Library_,
                     const Arg Arguments[],
                     const char* ArgumentTypes_,
					 bool Volatile_=false); 

	std::string GetFunctionName() const;
	std::string GetExcelFunctionName() const;
	std::string GetFunctionDescription() const;
	std::string GetLibrary() const;
	int GetNoOfArguments() const;
	std::vector<std::string> GetArgumentNames() const;
	std::vector<std::string> GetArgumentDescriptions() const;
	std::string GetArgumentTypes() const;

	bool GetVolatile() const
	{
		return Volatile;
	}
  
private:

	std::string FunctionName;
	std::string ExcelFunctionName;
	std::string FunctionDescription;
	std::string Library;
	int NoOfArguments;
	std::vector<std::string> ArgumentNames;
	std::vector<std::string> ArgumentDescriptions;
	std::string ArgumentTypes;
	bool Volatile;


};

class XLFunctionRegistrationHelper
{
public:
  
	XLFunctionRegistrationHelper(const std::string& FunctionName,
                     const std::string& ExcelFunctionName,
                     const std::string& FunctionDescription,
                     const std::string& Library,
                     const Arg Args[],
                     const char* Types,
					 bool Volatile=false); 
  
private:
  
};


//! singleton pattern, cf the Factory
class ExcelFunctionRegistrationRegistry
{
public:

	static ExcelFunctionRegistrationRegistry& Instance();

	void DoTheRegistrations() const;
	void AddFunction(const XLFunctionRegistrationData&);

private:
	ExcelFunctionRegistrationRegistry();
	ExcelFunctionRegistrationRegistry(const ExcelFunctionRegistrationRegistry& original);

	std::list<XLFunctionRegistrationData> RegistrationData;
	
};

}

#endif 
