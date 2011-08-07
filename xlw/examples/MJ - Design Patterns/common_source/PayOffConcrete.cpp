//
//
//                                                PayOffConcrete.cpp
//
//

#include "PayOffConcrete.h"
#include "ArgListFactory.h"

PayOffCall::PayOffCall(xlw::ArgumentList args)
{
    if (args.GetStructureName() != "payoff") // must be lower case here
        THROW_XLW("payoff structure expected in PayOffCall class");

    if (args.GetStringArgumentValue("name") != "call")
        THROW_XLW("payoff list not for call passed to PayOffCall : got " << args.GetStringArgumentValue("name"));

    Strike = args.GetDoubleArgumentValue("strike");

    args.CheckAllUsed("PayOffCall");
}

double PayOffCall::operator () (double Spot) const
{
    return Spot-Strike > 0.0 ? Spot-Strike  :0.0;
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}


double PayOffPut::operator () (double Spot) const
{
    return Strike-Spot > 0.0 ? Strike-Spot   :0.0;
;
}

PayOffPut::PayOffPut(xlw::ArgumentList args)
{
    if (args.GetStructureName() != "payoff") // must be lower case here
        THROW_XLW("payoff structure expected in PayOffCall class");

    if (args.GetStringArgumentValue("name") != "put")
        THROW_XLW("payoff list not for put passed to PayOffPut : got " << args.GetStringArgumentValue("name"));

    Strike = args.GetDoubleArgumentValue("strike");

    args.CheckAllUsed("PayOffPut");
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}


double PayOffSpread::operator () (double Spot) const
{
    return Volume1*(*OptionOne)(Spot)+Volume2*(*OptionTwo)(Spot);
;
}

PayOffSpread::PayOffSpread(xlw::ArgumentList args)
{
    if (args.GetStructureName() != "payoff") // must be lower case here
        THROW_XLW("payoff structure expected in PayOffCall class");

    if (args.GetStringArgumentValue("name") != "spread")
        THROW_XLW("payoff list not for spread passed to payoffspread : got " << args.GetStringArgumentValue("name"));

    if (!args.GetIfPresent("Volume1",Volume1))
        Volume1= 1.0;

    if (!args.GetIfPresent("Volume2",Volume2))
        Volume2= -1.0;

    OptionOne = Wrapper<PayOff>(xlw::GetFromFactory<PayOff>(args.GetArgumentListArgumentValue("optionone")));
    OptionTwo = Wrapper<PayOff>(xlw::GetFromFactory<PayOff>(args.GetArgumentListArgumentValue("optiontwo")));

    args.CheckAllUsed("PayOffSpread");
}

PayOff* PayOffSpread::clone() const
{
    return new PayOffSpread(*this);
}

