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

#include "Outputter.h"

void PushBack(std::string& str, char c)
{
	std::string tmp("0");
	tmp[0]=c;
	str.append(tmp);

}
void AddLine(std::vector<char>& file, std::string line)
{
	for (unsigned long i=0; i < line.size(); i++)
		file.push_back(line[i]);

	file.push_back('\n');
}

std::vector<char> OutputFileCreator(const std::vector<FunctionDescription>& functionDescriptions,
									std::string inputFileName, std::string LibraryName)
{
	std::vector<char> output;
	AddLine(output, "//// ");
	AddLine(output, "//// created by xlwplus");
	AddLine(output, "////");
	AddLine(output,"");
	AddLine(output,"#include <xlw/pragmas.h>");
	AddLine(output,"#include <xlw/MyContainers.h>");
	AddLine(output,"#include <xlw/CellMatrix.h>");
	AddLine(output, "#include \""+inputFileName+"\"");
	AddLine(output, "#include <xlw/xlw.h>");
	AddLine(output, "#include <xlw/XlFunctionRegistration.h>");
	AddLine(output, "#include <stdexcept>");
	AddLine(output,"#include <xlw/XlOpenClose.h>");
	AddLine(output,"namespace {");
	AddLine(output,"const char* LibraryName = \""+LibraryName+"\";");
	AddLine(output,"};");
	AddLine(output,"");
	AddLine(output,"// dummy function to force linkage");
	AddLine(output,"namespace {");
	AddLine(output,"void DummyFunction()");
	AddLine(output,"{");
	AddLine(output,"xlAutoOpen();");
	AddLine(output,"xlAutoClose();");
	AddLine(output,"}");
	AddLine(output,"}");

	AddLine(output,"");
	AddLine(output,"// registrations start here");
	AddLine(output,"");	
	AddLine(output,"");

	for (unsigned long i=0; i < functionDescriptions.size(); i++)
	{
		std::string name = functionDescriptions[i].GetFunctionName();
		std::string keys;
		AddLine(output,"namespace");
		AddLine(output,"{");
    
		AddLine(output,"XLRegistration::Arg");
		AddLine(output,name+"Args[]=");

		AddLine(output,"{");
    
		{for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
		{
			PushBack(keys,functionDescriptions[i].GetArgument(j).GetTheType().GetEXCELKey());
			std::string thisLine = "{ \"";
			thisLine+= functionDescriptions[i].GetArgument(j).GetArgumentName();
			thisLine+= "\",\"";
			thisLine+= functionDescriptions[i].GetArgument(j).GetArgumentDescription();
			thisLine+=" \"}";

		if (j+1< functionDescriptions[i].NumberOfArguments())
			thisLine+=",";

		    AddLine(output,thisLine);
		}}
	
		AddLine(output,"};");
		// ok arg list is now set up
    

	    AddLine(output,"  XLRegistration::XLFunctionRegistrationHelper"); 
        AddLine(output,"register"+name+"(\"xl"+name+"\",");
		AddLine(output,"\""+name+"\",");
		AddLine(output,"\""+ functionDescriptions[i].GetFunctionDescription()+" \",");
		AddLine(output, "LibraryName,");
        AddLine(output,name+"Args,");
		AddLine(output,"\""+keys+"\");");
		AddLine(output,"}");

		// ok we've done the registration, we still need to do the function

		AddLine(output,"");
		AddLine(output,"");
		AddLine(output,"");

	
		AddLine(output,"extern \"C\"");
		AddLine(output,"{");

		AddLine(output,"LPXLOPER EXCEL_EXPORT");
		AddLine(output,"xl"+name+"(");
	
	
		{for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
		{
			std::string delimiter;
			if (j +1 < functionDescriptions[i].NumberOfArguments())
				delimiter = ",";
			else 
				delimiter = ")";

			AddLine(output,"LPXLOPER xl"+functionDescriptions[i].GetArgument(j).GetArgumentName()+"_"+delimiter);
	
		}}



	AddLine(output,"{");
	AddLine(output,"EXCEL_BEGIN;");
	AddLine(output,"");
	AddLine( output, "\tif (XlfExcel::Instance().IsCalledByFuncWiz())");
    AddLine(output,"\t\treturn XlfOper(true);");
 	AddLine(output,"");

	{for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
	{
		AddLine(output,"XlfOper xl"+functionDescriptions[i].GetArgument(j).GetArgumentName()+"(xl"+
			functionDescriptions[i].GetArgument(j).GetArgumentName()+"_);");

		AddLine(output,functionDescriptions[i].GetArgument(j).GetTheType().GetNameIdentifier()+" "+
				functionDescriptions[i].GetArgument(j).GetArgumentName()+"(xl"+
				functionDescriptions[i].GetArgument(j).GetArgumentName()+functionDescriptions[i].GetArgument(j).GetTheType().GetConversionToMethod()
				+"(\""+functionDescriptions[i].GetArgument(j).GetArgumentName()+"\")"
				+");");
				AddLine(output,"");
	}}
	AddLine(output,functionDescriptions[i].GetReturnType()+" result(");
	AddLine(output,'\t'+functionDescriptions[i].GetFunctionName()+"(");
	for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
		{
			std::string delimiter;
			if (j +1 < functionDescriptions[i].NumberOfArguments())
				delimiter = ",";
			else 
				delimiter = ")";

			AddLine(output,"\t\t"+functionDescriptions[i].GetArgument(j).GetArgumentName()+delimiter);
		}
	AddLine(output,"\t);");

	

	 AddLine(output,"return XlfOper(result);");

	AddLine(	output,"EXCEL_END");

	AddLine(output,"}");

	AddLine(output,"}");

	AddLine(output,"");
	AddLine(output,"");
	AddLine(output,"");
	AddLine(output,"//////////////////////////");
	AddLine(output,"");

	}
	return output;

}
