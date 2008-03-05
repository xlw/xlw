//
//
//                                                            ArgListArgListFactory.h
//
//

#ifndef ARG_LIST_FACTORY_HELPER_H
#define ARG_LIST_FACTORY_HELPER_H
#include <xlw/ArgListFactory.h>
#include <string>

namespace xlw {

    template<class TBase, class TDerived>
    class FactoryHelper
    {
    public:
      FactoryHelper(std::string);
      static TBase* create(const ArgumentList&);
      ~FactoryHelper(){}
    };


    template<class TBase, class TDerived>
    FactoryHelper<TBase,TDerived>::FactoryHelper(std::string id)
    {
        MakeLowerCase(id);
        ArgListFactory<TBase>::FactoryInstance().RegisterClass(id, FactoryHelper<TBase,TDerived>::create);
    }


    template<class TBase, class TDerived>
    TBase*
    FactoryHelper<TBase,TDerived>::create(const ArgumentList& Input)
    {
      return new TDerived(Input);
    }

}

#endif
