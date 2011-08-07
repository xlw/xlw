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

#include <clw/Dispatcher.h>

#include <xlw/ArgList.h>

#ifdef USE_CLW_CODE

namespace
clw
{
  using namespace xlw;
  CellMatrix Dispatcher::CallFunction(const ArgumentList& args) const
  {
    std::string Id = args.GetStructureName();

    xlw::MakeLowerCase(Id);
    if  (DispatchMap.find(Id) == DispatchMap.end())
    {
      THROW_XLW(Id << " is an unknown function. Known functions are " << KnownFunctions);
    }

    return (DispatchMap.find(Id)->second)(args);

  }


  void Dispatcher::RegisterFunction(std::string FunctionId, FunctionToCall function)
  {
    xlw::MakeLowerCase(FunctionId);
    KnownFunctions+=" "+FunctionId;

    DispatchMap.insert(std::pair<std::string,FunctionToCall>(FunctionId,function));

  }

  DispatcherHelper::DispatcherHelper(const std::string& id, FunctionToCall function)
  {
   Dispatcher::Instance().RegisterFunction(id,function);
  }


}
#else
#ifdef _MSC_VER
// avoid linker warnings
namespace
{
    char dummy = 0;
}
#endif
#endif
