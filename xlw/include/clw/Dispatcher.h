//
//
//                Dispatcher.h
//
//

#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <map>
#include <string>
#include <xlw/CellMatrix.h>

#include <xlw/ArgList.h>



  typedef xlw::CellMatrix (*FunctionToCall)( xlw::ArgumentList);


namespace
clw
{
 typedef xlw::CellMatrix (*FunctionToCall)( xlw::ArgumentList);



class Dispatcher
{
public:

  static Dispatcher& Instance()
  {
    static Dispatcher single;
    return single;
  }

  xlw::CellMatrix CallFunction(const xlw::ArgumentList&) const;

  void RegisterFunction(std::string FunctionId, FunctionToCall);



private:
  Dispatcher(){}
  Dispatcher(const Dispatcher&){}

  std::map<std::string, FunctionToCall> DispatchMap;

  std::string KnownFunctions;

};

class DispatcherHelper
{
public:

  DispatcherHelper(const std::string& id, FunctionToCall);

private:

};

}

#endif
