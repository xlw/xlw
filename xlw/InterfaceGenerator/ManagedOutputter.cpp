/*
 Copyright (C) 2011 Narinder Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - https://xlw.github.io/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "ManagedOutputter.h"


void writePreamble(std::vector<char> &outputVector)
{
  AddLine(outputVector, "//// ");
  AddLine(outputVector, "//// Autogenerated by xlw ");
  AddLine(outputVector, "//// Do not edit this file, it will be overwritten ");
  AddLine(outputVector, "//// by InterfaceGenerator ");
  AddLine(outputVector, "////");
  AddLine(outputVector,"");
  AddLine(outputVector,"#include \"xlw/MyContainers.h\"");
  AddLine(outputVector,"#include <xlw/CellMatrix.h>");
  AddLine(outputVector,"#include <stdexcept>");

}




void OutputFileCreatorMan(std::vector<FunctionDescription>& functionDescriptions,
                                      std::string inputFileName,
                                      std::string LibraryName,
                                      std::vector<char> &outputVector_h,
                                      std::vector<char> &outputVector_cpp
                                       )

{
  writePreamble(outputVector_h);
  writePreamble(outputVector_cpp);

  AddLine(outputVector_cpp,"#include \""+strip(inputFileName)+"\"");
  AddLine(outputVector_cpp,"#include <xlw/xlwManaged.h>");
  AddLine(outputVector_cpp,"using namespace System;");
  AddLine(outputVector_cpp,"using namespace Runtime::InteropServices;");

  AddLine(outputVector_h,"using namespace xlw;");

  const std::set<std::string>& includes = IncludeRegistry<native>::Instance().GetIncludes();
  for (std::set<std::string>::const_iterator it = includes.begin(); it!= includes.end(); ++it)
  {
    AddLine(outputVector_cpp, "#include "+*it+"\n");
    AddLine(outputVector_h, "#include "+*it+"\n");
  }


  const std::set<std::string>& usings = IncludeRegistry<managed>::Instance().GetIncludes();
  for (std::set<std::string>::const_iterator it = usings.begin(); it!= usings.end(); ++it)
  {
    AddLine(outputVector_cpp, "using namespace "+*it+";\n");
  }


  AddLine(outputVector_cpp, "\n\n\n\n");
  AddLine(outputVector_h, "\n\n\n\n");
  
  

  for (unsigned long i=0; i < functionDescriptions.size(); i++)
  {
	bool isCommand(functionDescriptions[i].GetReturnType() == "void");

	if (isCommand)
	{
		AddLine(outputVector_h, "void //" + functionDescriptions[i].GetFunctionDescription());
		AddLine(outputVector_h,  functionDescriptions[i].GetFunctionName() +"();");
		AddLine(outputVector_h, "\n\n\n\n");
	}
	else
	{

    std::vector<std::string> body;
    std::string returnType = functionDescriptions[i].GetReturnType();
    std::string name       = functionDescriptions[i].GetFunctionName();
    std::string mxlw_name  = "mxlw_" + name;
    functionDescriptions[i].setFunctionName(mxlw_name);
    AddLine(outputVector_cpp,returnType + " " + mxlw_name);
	AddLine(outputVector_cpp, "\t\t(");
	AddLine(outputVector_h,returnType + "  // " +functionDescriptions[i].GetFunctionDescription() );
    AddLine(outputVector_h, mxlw_name + "\t\t(");

    std::string passingParamString = "(";
     for (unsigned long j=0; j < functionDescriptions[i].NumberOfArguments(); j++)
    {
      std::string thisBody;
	  std::string argName = functionDescriptions[i].GetArgument(j).GetArgumentName();;
      std::string paramString = functionDescriptions[i].GetArgument(j).GetTheType().GetNameIdentifier()
                                + " " + functionDescriptions[i].GetArgument(j).GetArgumentName();
      

	   std::vector<std::string> chain = functionDescriptions[i].GetArgument(j).GetTheType().GetConversionChain();
       std::vector<std::string>::const_iterator it = chain.begin()+chain.size()-1;

	   
	   
             passingParamString += argName;
      
	  
             char id = 'a';

              std::string lastId = functionDescriptions[i].GetArgument(j).GetArgumentName()+id;
              ++id;

              for (unsigned long k=0; k < chain.size() -1; k++)
              {
                std::vector<std::string>::const_iterator it = chain.begin()+chain.size()-2-k;
                std::string newId = functionDescriptions[i].GetArgument(j).GetArgumentName();

                if (k+1 != chain.size() -1)
                  newId+= id;

                TypeRegistry<managed>::regData argData = TypeRegistry<managed>::Instance().GetRegistration(*it);
                thisBody+= "\t\t\t" + argData.NewType+" "+newId+"(";

                bool specIdentifier = argData.TakesIdentifier;
                std::string identifierBit;
                bool isMethod = argData.IsAMethod;

                if (specIdentifier && !isMethod)
                  identifierBit = ",\""+newId+"\"";
                if (specIdentifier && isMethod)
                  identifierBit = "\""+newId+"\"";


                if (isMethod)
                  thisBody+= " "+lastId+"."+argData.Converter+"("+identifierBit+" ));\n";
                else
                  thisBody+= " "+argData.Converter+"("+lastId+identifierBit+" ));\n";

                ++id;
                lastId=newId;
			  }

	  std::string uniqifier("a");
      if ((chain.size() ==1))
	  {     lastId = functionDescriptions[i].GetArgument(j).GetArgumentName();
            uniqifier ="";
      }
	  paramString = "\t\t"   + (*it) + " " + lastId+uniqifier;
	  std::string hparamString = "\t\t"   + (*it) + " " + functionDescriptions[i].GetArgument(j).GetArgumentName();

      std::string termChar = ",";
      std::string colon = "";
      if(j==functionDescriptions[i].NumberOfArguments()-1)
      {
          termChar="";
          colon = " );";
      }
      passingParamString +=termChar+colon;
      paramString+=termChar;
	  hparamString+=termChar;
      AddLine(outputVector_cpp,paramString);
	  AddLine(outputVector_h,hparamString+ " //" + functionDescriptions[i].GetArgument(j).GetArgumentDescription());
	  if(colon!="")
	  {
	     AddLine(outputVector_h, colon);
	  }
	  body.push_back(thisBody);
     }
      AddLine(outputVector_cpp,"\t\t)");
      AddLine(outputVector_cpp,"\t\t{");
      AddLine(outputVector_cpp,"\t\tMANAGED_EXECL_BEGIN");
	  for(size_t bi(0); bi < body.size(); ++bi)
	  {
	       if(!body[bi].empty())
		   {
	           AddLine(outputVector_cpp,body[bi]);
		   }
      }
      AddLine(outputVector_cpp,"\t\t\treturn " + name + passingParamString);
      AddLine(outputVector_cpp,"\t\tMANAGED_EXECL_END");
      AddLine(outputVector_cpp,"\t\t}");
	  AddLine(outputVector_cpp,"");
	  AddLine(outputVector_cpp,"////////////////////////////////////");
	  AddLine(outputVector_cpp,"");

	  }
  }






  


}


