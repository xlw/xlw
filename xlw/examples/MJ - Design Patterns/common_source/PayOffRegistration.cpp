//
//
//                                                                PayOffRegistration.cpp
//
//
#include "ArgListFactoryHelper.h"
#include "PayOffConcrete.h"

namespace
{
    xlw::FactoryHelper<PayOff,PayOffCall> callHelper("call");
    xlw::FactoryHelper<PayOff,PayOffPut> putHelper("put");
    xlw::FactoryHelper<PayOff,PayOffSpread> spreadHelper("spread");

}
