//
//
//                            PayOff.h
//
//

#ifndef PAYOFF_H
#define PAYOFF_H
class PayOff
{
public:

    PayOff();

    virtual double operator()(double Spot) const=0;
    virtual ~PayOff();
    virtual PayOff* clone() const=0;

private:
    
};
#endif
