//
//
//                                        PayOffConcrete.h
//
//
#ifndef PAYOFF_CONCRETE_H
#define PAYOFF_CONCRETE_H

#include "PayOff.h"
#include <xlw/ArgList.h>
#include <xlw/Wrapper.h>


class PayOffCall : public PayOff
{
public:

    PayOffCall(ArgumentList args);

    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const; // change to PayOffCall* if your compiler is up to date

private:

    double Strike;

};


class PayOffPut : public PayOff
{
public:

    PayOffPut(ArgumentList args);

    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};


class PayOffSpread : public PayOff
{
public:

    PayOffSpread(ArgumentList args);

    virtual double operator()(double Spot) const;
    virtual ~PayOffSpread(){}
    virtual PayOff* clone() const;

private:
    Wrapper<PayOff> OptionOne;
    Wrapper<PayOff> OptionTwo;
    double Volume1;
    double Volume2;

};


#endif
