
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

#ifndef PARSER_DATA_H
#define PARSER_DATA_H
#include <string>
#include <vector>

class  FunctionArgumentType
{
public:
     FunctionArgumentType(std::string NameIdentifier,
                          const std::vector<std::string>& ConversionChain,
                          const std::string& EXCELKey);

     const std::string& GetNameIdentifier() const;
     const std::vector<std::string>& GetConversionChain() const;
     const std::string &GetEXCELKey() const;

private:
     std::string NameIdentifier;
     std::vector<std::string> ConversionChain;
     std::string EXCELKey;

};

class FunctionArgument
{
public:
     FunctionArgument(const FunctionArgumentType& TheType_,
                        std::string ArgumentName_,
                        std::string ArgumentDescription_);

     FunctionArgumentType GetTheType() const;
     std::string GetArgumentName() const;
     std::string GetArgumentDescription() const;

private:
     FunctionArgumentType TheType;
     std::string ArgumentName;
     std::string ArgumentDescription;
};

class FunctionDescription
{
public:
     FunctionDescription(std::string FunctionName_,
                         std::string FunctionHelpDescription_,
                         std::string ReturnType,
                         const std::string& ExcelKey,
                         const std::vector<FunctionArgument>& Arguments_,
                         bool Volatile_,
                         bool Time_,
                         bool Threadsafe_,
                         std::string helpID_,
                         bool Asynchronous_,
                         bool MacroSheet_,
                         bool ClusterSafe_);

     std::string GetFunctionName() const;
     std::string GetDisplayName() const;
     std::string GetFunctionDescription() const;
     std::string GetExcelKey() const;
     std::string GetReturnType() const;
     const FunctionArgument& GetArgument(unsigned long ArgumentNumber) const;
     unsigned long NumberOfArguments() const;
     bool GetVolatile() const;
     bool DoTime() const;
     bool GetThreadsafe() const;
     std::string GetHelpID() const;
     bool GetAsynchronous() const;
     bool GetMacroSheet() const;
     bool GetClusterSafe() const;
     void setFunctionName(const std::string &newName);

	 static void Transit(const std::vector<FunctionDescription> &source, 
			 std::vector<FunctionDescription> & destination);



private:
     std::string FunctionName;
     std::string DisplayName;
     std::string FunctionHelpDescription;
     std::string ReturnType;
     std::string ExcelKey;
     std::string helpID;
     std::vector<FunctionArgument> Arguments;
     bool Volatile;
     bool Time;
     bool Threadsafe;
     bool Asynchronous;
     bool MacroSheet;
     bool ClusterSafe;
};





#endif
