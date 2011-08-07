/*
 Copyright (C) 2005 Mark Joshi


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef ARG_LIST_FACTORY_HELPER_H
#define ARG_LIST_FACTORY_HELPER_H
#include "ArgListFactory.h"
#include <map>
#include <string>
#include <xlw/PascalStringConversions.h>


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
        StringUtilities::makeLower(id);
        ArgListFactory<TBase>::Instance().RegisterClass(id, FactoryHelper<TBase,TDerived>::create);
    }


    template<class TBase, class TDerived>
    TBase*
    FactoryHelper<TBase,TDerived>::create(const ArgumentList& Input)
    {
      return new TDerived(Input);
    }

}

#endif
