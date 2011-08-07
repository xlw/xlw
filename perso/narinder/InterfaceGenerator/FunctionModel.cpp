
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
#include "FunctionModel.h"
#include "IncludeRegister.h"

FunctionModel::FunctionModel(std::string ReturnType_, std::string Name, std::string Description,
                  bool Volatile_, bool Time_, bool Threadsafe_,
                  std::string helpID_,bool Asynchronous_,bool MacroSheet_, bool ClusterSafe_)
: ReturnType(ReturnType_), FunctionName(Name), FunctionDescription(Description), helpID(helpID_),
  Volatile(Volatile_), Time(Time_), Threadsafe(Threadsafe_),
  Asynchronous(Asynchronous_),MacroSheet(MacroSheet_),ClusterSafe(ClusterSafe_)
{
}

void FunctionModel::AddArgument(std::string Type_, std::string Name_, std::string Description_)
{
    ArgumentTypes.push_back(Type_);
    ArgumentNames.push_back(Name_);
    ArgumentDescs.push_back(Description_);
}

size_t FunctionModel::GetNumberArgs() const
{
    return ArgumentTypes.size();
}
