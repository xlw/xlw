//
//
//                          Dispatcher.cpp
//
//

#include <clw/Dispatcher.h>

#include <xlw/ArgList.h>
namespace
clw
{
  using namespace xlw;
  CellMatrix Dispatcher::CallFunction(const ArgumentList& args) const
  {
    std::string Id = args.GetStructureName();


    if  (DispatchMap.find(Id) == DispatchMap.end())
    {
      std::string message(Id+" is an unknown function. Known functions are "+KnownFunctions);
      return message;
    }

    return (DispatchMap.find(Id)->second)(args);

  }


  void Dispatcher::RegisterFunction(std::string FunctionId, FunctionToCall function)
  {
    KnownFunctions+=" "+FunctionId;

    DispatchMap.insert(std::pair<std::string,FunctionToCall>(FunctionId,function));

  }

  DispatcherHelper::DispatcherHelper(const std::string& id, FunctionToCall function)
  {
   Dispatcher::Instance().RegisterFunction(id,function); 
  }


}
