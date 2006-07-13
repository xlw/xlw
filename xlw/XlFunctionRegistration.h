
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
                     const char* ArgumentTypes_); 

	std::string GetFunctionName() const;
	std::string GetExcelFunctionName() const;
	std::string GetFunctionDescription() const;
	std::string GetLibrary() const;
	int GetNoOfArguments() const;
	std::vector<std::string> GetArgumentNames() const;
	std::vector<std::string> GetArgumentDescriptions() const;
	std::string GetArgumentTypes() const;
  
private:

	std::string FunctionName;
	std::string ExcelFunctionName;
	std::string FunctionDescription;
	std::string Library;
	int NoOfArguments;
	std::vector<std::string> ArgumentNames;
	std::vector<std::string> ArgumentDescriptions;
	std::string ArgumentTypes;


};

class XLFunctionRegistrationHelper
{
public:
  
	XLFunctionRegistrationHelper(const std::string& FunctionName,
                     const std::string& ExcelFunctionName,
                     const std::string& FunctionDescription,
                     const std::string& Library,
                     const Arg Args[],
                     const char* Types); 
  
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
