
/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2007, 2008 Eric Ehlers

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
#include "Outputter.h"
#include "TypeRegister.h"
#include "IncludeRegister.h"
#include <sstream>

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

std::string strip(std::string in) {
  for (size_t i=in.length(); i; --i)
    if (in[i] == '/' || in[i] == '\\')
      return in.substr(i + 1, in.length() - i);
  return in;
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
  AddLine(output, "#include \""+strip(inputFileName)+"\"");
  AddLine(output, "#include <xlw/xlw.h>");
  AddLine(output, "#include <xlw/XlFunctionRegistration.h>");
  AddLine(output, "#include <stdexcept>");
  AddLine(output,"#include <xlw/XlOpenClose.h>");
  AddLine(output,"#include <ctime>");
  AddLine(output,"using namespace xlw;");


  const std::set<std::string>& includes = IncludeRegistry::Instance().GetIncludes();
  for (std::set<std::string>::const_iterator it = includes.begin(); it!= includes.end(); ++it)
  {
    AddLine(output, "#include "+*it+"\n");
  }

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
    //std::string keys;
    AddLine(output,"namespace");
    AddLine(output,"{");

    AddLine(output,"XLRegistration::Arg");
    AddLine(output,name+"Args[]=");

    AddLine(output,"{");

    {for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {
      //PushBack(keys,functionDescriptions[i].GetArgument(j).GetTheType().GetEXCELKey());
      std::string thisLine = "{ \"";
      thisLine+= functionDescriptions[i].GetArgument(j).GetArgumentName();
      thisLine+= "\",\"";
      thisLine+= functionDescriptions[i].GetArgument(j).GetArgumentDescription();
      thisLine+= " \",\"";
      thisLine+= functionDescriptions[i].GetArgument(j).GetTheType().GetEXCELKey();
      thisLine+="\"}";

      if (j+1< functionDescriptions[i].NumberOfArguments())
        thisLine+=",";

      AddLine(output,thisLine);
    }}

    if (functionDescriptions[i].NumberOfArguments() == 0)
      AddLine(output, " { \"\",\"\" } ");

    AddLine(output,"};");
    // ok arg list is now set up

    std::ostringstream s;
    s << functionDescriptions[i].NumberOfArguments();

    AddLine(output,"  XLRegistration::XLFunctionRegistrationHelper"); 
    AddLine(output,"register"+name+"(\"xl"+name+"\",");
    AddLine(output,"\""+name+"\",");
    AddLine(output,"\""+ functionDescriptions[i].GetFunctionDescription()+" \",");
    AddLine(output, "LibraryName,");
    AddLine(output,name+"Args,");
    AddLine(output,s.str());
    //AddLine(output,"\""+keys+"\"");
    if ( functionDescriptions[i].GetVolatile())
      AddLine(output,",true");
    else
      AddLine(output,",false");
    if ( functionDescriptions[i].GetThreadsafe())
      AddLine(output,",true");

    AddLine(output, ");");
    AddLine(output,"}");

    // ok we've done the registration, we still need to do the function

    AddLine(output,"");
    AddLine(output,"");
    AddLine(output,"");


    AddLine(output,"extern \"C\"");
    AddLine(output,"{");

    //AddLine(output,"LPXLOPER EXCEL_EXPORT");
    AddLine(output,"LPXLFOPER EXCEL_EXPORT");
    AddLine(output,"xl"+name+"(");


    {for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {
      std::string delimiter;
      if (j +1 < functionDescriptions[i].NumberOfArguments())
        delimiter = ",";
      else 
        delimiter = ")";

      std::vector<std::string> chain = functionDescriptions[i].GetArgument(j).GetTheType().GetConversionChain();
      std::vector<std::string>::const_iterator it = chain.begin()+chain.size()-1;

      std::string uniqifier("a");
      if (chain.size() ==1)
        uniqifier ="";

      AddLine(output,*it+" "+functionDescriptions[i].GetArgument(j).GetArgumentName()+uniqifier+delimiter);

    }}

    if (functionDescriptions[i].NumberOfArguments()==0)
      AddLine(output, ")");



    AddLine(output,"{");
    AddLine(output,"EXCEL_BEGIN;");
    AddLine(output,"");
    AddLine( output, "\tif (XlfExcel::Instance().IsCalledByFuncWiz())");
    AddLine(output,"\t\treturn XlfOper(true);");
    AddLine(output,"");

    {for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {

      // we converted to XlfOper now we have to go through our conversion chain

      std::vector<std::string> chain = functionDescriptions[i].GetArgument(j).GetTheType().GetConversionChain();
      char id = 'a';

      std::string lastId = functionDescriptions[i].GetArgument(j).GetArgumentName()+id;
      ++id;

      for (unsigned long k=0; k < chain.size() -1; k++)
      {
        std::vector<std::string>::const_iterator it = chain.begin()+chain.size()-2-k;
        std::string newId = functionDescriptions[i].GetArgument(j).GetArgumentName();

        if (k+1 != chain.size() -1)
          newId+= id;

        TypeRegistry::regData argData = TypeRegistry::Instance().GetRegistration(*it);        
        AddLine(output, argData.NewType+" "+newId+"(");

        bool specIdentifier = argData.TakesIdentifier;
        std::string identifierBit;
        bool isMethod = argData.IsAMethod;

        if (specIdentifier && !isMethod)
          identifierBit = ",\""+newId+"\"";
        if (specIdentifier && isMethod)
          identifierBit = "\""+newId+"\"";


        if (isMethod)
          AddLine(output, "\t"+lastId+"."+argData.Converter+"("+identifierBit+"));");
        else 
          AddLine(output, "\t"+argData.Converter+"("+lastId+identifierBit+"));");

        ++id;
        lastId=newId;
      }

      AddLine(output,"");

    }}

    if (functionDescriptions[i].DoTime())
    {
      AddLine(output," double t = (clock()+0.0)/CLOCKS_PER_SEC;");
    }

    AddLine(output,functionDescriptions[i].GetReturnType()+" result(");
    if (functionDescriptions[i].NumberOfArguments() >0)
    {
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
    }
    else
      AddLine(output,'\t'+functionDescriptions[i].GetFunctionName()+"());");

    if (functionDescriptions[i].DoTime())
    {
      AddLine(output,"  t = (clock()+0.0)/CLOCKS_PER_SEC-t;");
      AddLine(output,"CellMatrix resultCells(result);");
      AddLine(output,"CellMatrix time(1,2);");
      AddLine(output,"time(0,0) = \"time taken\";");
      AddLine(output,"time(0,1) = t;");
      AddLine(output,"resultCells.PushBottom(time);");
      AddLine(output,"return XlfOper(resultCells);");
    }
    else
    {
      AddLine(output,"return XlfOper(result);");
    }
    AddLine(    output,"EXCEL_END");

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

std::vector<char> OutputFileCreatorCL(const std::vector<FunctionDescription>& functionDescriptions,
                                      std::string inputFileName)
{
  std::vector<char> output;
  AddLine(output, "//// ");
  AddLine(output, "//// created by xlwplus");
  AddLine(output, "////");
  AddLine(output,"");
  AddLine(output,"#include <xlw/pragmas.h>");
  
  AddLine(output,"#include <clw/Dispatcher.h>");
  AddLine(output,"#include <xlw/MyContainers.h>");
  AddLine(output,"#include <xlw/CellMatrix.h>");
  AddLine(output, "#include \""+strip(inputFileName)+"\"");
  AddLine(output, "#include <xlw/xlw.h>");
  AddLine(output, "#include <xlw/XlFunctionRegistration.h>");
  AddLine(output, "#include <stdexcept>");
  AddLine(output,"#include <xlw/XlOpenClose.h>");
  AddLine(output,"#include <ctime>");

  const std::set<std::string>& includes = IncludeRegistry::Instance().GetIncludes();
  for (std::set<std::string>::const_iterator it = includes.begin(); it!= includes.end(); ++it)
  {
    AddLine(output, "#include "+*it+"\n");
  }



  AddLine(output,"");
  AddLine(output,"");
  AddLine(output,"");


  AddLine(output," namespace \n{");
  for (unsigned long i=0; i < functionDescriptions.size(); i++)
  {


    std::string name = functionDescriptions[i].GetFunctionName();

    AddLine(output,"CellMatrix cl"+name+"(ArgumentList arguments)  ");




    AddLine(output,"{");
    AddLine(output,"");

    for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {
      std::vector<std::string> chain 
        = functionDescriptions[i].GetArgument(j).GetTheType().GetConversionChain();


      while (chain.size() > 0 && (*chain.rbegin() == "XlfOper" || *chain.rbegin() == "LPXLFOPER" || 
        *chain.rbegin() == "LPXLARRAY"
        || *chain.rbegin() == "XLWSTR") )
        chain.pop_back(); // ditch EXCEL types

      if (chain.size() ==0)
        throw("Command line interface requires non-xlw types. Broke on "+name+" "+functionDescriptions[i].GetArgument(j).GetArgumentName());


      bool furtherConversionsNecessary = (chain.size() > 1);

      std::string fundamentalType = *(chain.rbegin());

      std::string argIdentifier(functionDescriptions[i].GetArgument(j).GetArgumentName());
      std::string variableName(argIdentifier);

      if (furtherConversionsNecessary)
        argIdentifier.push_back('a');

      AddLine(output,fundamentalType+" "+argIdentifier+"(");

     
      //double, NEMatrix, short, MyArray, MyMatrix, CellMatrix, string, std::string

      if (fundamentalType == "double")
      {
        AddLine(output, "arguments.GetDoubleArgumentValue(\""+variableName+"\"));");
      }
      else
        if (fundamentalType == "NEMatrix")
        {
          AddLine(output, "arguments.GetMatrixArgumentValue(\""+variableName+"\"));");
        }
        else 
          if (fundamentalType == "short")
          {
            AddLine(output, "static_cast<short>(arguments.GetDoubleArgumentValue(\""+variableName+"\")));");
          }
          else 
            if (fundamentalType == "MyArray")
            {
              AddLine(output, "arguments.GetArrayArgumentValue(\""+variableName+"\"));");
            }
            else 
              if (fundamentalType == "MyMatrix")
              {
                AddLine(output, "arguments.GetMatrixArgumentValue(\""+variableName+"\"));");
              }
              else 
                if (fundamentalType == "CellMatrix")
                {
                  AddLine(output, "arguments.GetCellsArgumentValue(\""+variableName+"\"));");
                }
                else 
                  if (fundamentalType == "string" || fundamentalType == "std::string"  || fundamentalType == "std::wstring" )
                  {
                    AddLine(output, "arguments.GetCellsArgumentValue(\""+variableName+"\"));");
                  }
                  else
                    throw("unknown type found: "+fundamentalType);








    }


    {for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {



      std::vector<std::string> chain = functionDescriptions[i].GetArgument(j).GetTheType().GetConversionChain();

      while (chain.size() > 0 && (*chain.rbegin() == "XlfOper" || *chain.rbegin() == "LPXLFOPER" || 
        *chain.rbegin() == "LPXLARRAY"
        || *chain.rbegin() == "XLWSTR") )
        chain.pop_back(); // ditch EXCEL types

      char id = 'a';

      std::string lastId = functionDescriptions[i].GetArgument(j).GetArgumentName()+id;
      ++id;

      for (unsigned long k=0; k < chain.size() -1; k++)
      {
        std::vector<std::string>::const_iterator it = chain.begin()+chain.size()-2-k;
        std::string newId = functionDescriptions[i].GetArgument(j).GetArgumentName();

        if (k+1 != chain.size() -1)
          newId+= id;

        TypeRegistry::regData argData = TypeRegistry::Instance().GetRegistration(*it);        
        AddLine(output, argData.NewType+" "+newId+"(");

        bool specIdentifier = argData.TakesIdentifier;
        std::string identifierBit;
        bool isMethod = argData.IsAMethod;

        if (specIdentifier && !isMethod)
          identifierBit = ",\""+newId+"\"";
        if (specIdentifier && isMethod)
          identifierBit = "\""+newId+"\"";


        if (isMethod)
          AddLine(output, "\t"+lastId+"."+argData.Converter+"("+identifierBit+"));");
        else 
          AddLine(output, "\t"+argData.Converter+"("+lastId+identifierBit+"));");

        ++id;
        lastId=newId;
      }

      AddLine(output,"");

    }}

    if (functionDescriptions[i].DoTime())
    {
      AddLine(output," double t = (clock()+0.0)/CLOCKS_PER_SEC;");
    }

    AddLine(output,functionDescriptions[i].GetReturnType()+" result(");
    if (functionDescriptions[i].NumberOfArguments() >0)
    {
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
    }
    else
      AddLine(output,'\t'+functionDescriptions[i].GetFunctionName()+"());");

    if (functionDescriptions[i].DoTime())
    {
      AddLine(output,"  t = (clock()+0.0)/CLOCKS_PER_SEC-t;");
      AddLine(output,"CellMatrix resultCells(result);");
      AddLine(output,"CellMatrix time(1,2);");
      AddLine(output,"time(0,0) = \"time taken\";");
      AddLine(output,"time(0,1) = t;");
      AddLine(output,"resultCells.PushBottom(time);");
      AddLine(output,"return resultCells;");
    }
    else
    {
      AddLine(output,"return result;");
    }


    AddLine(output,"}");

    AddLine(output,"");
    AddLine(output,"");

    //register with dispatcher
    AddLine(output, "clw::DispatcherHelper clhelper"+name+"(\""+name+"\",&cl"+name+");");

    AddLine(output,"");
    AddLine(output,"//////////////////////////");
    AddLine(output,"");

    

  }

  AddLine(output,"}");

  AddLine(output,"");
  AddLine(output,"");

  return output;

}
