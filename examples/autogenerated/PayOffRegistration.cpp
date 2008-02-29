//
//
//                                                                PayOffRegistration.cpp
//
//
#include <xlw/ArgListFactoryHelper.h>
#include "PayOffConcrete.h"

namespace
{
    FactoryHelper<PayOff,PayOffCall> callHelper("call");
    FactoryHelper<PayOff,PayOffPut> putHelper("put");
    FactoryHelper<PayOff,PayOffSpread> spreadHelper("spread");

}
