// PayOff3.cpp

#include "payoff4.h"
#include "minmax.h"

PayOffCall::PayOffCall(double strike_)
{
    strike = strike_;
}

double PayOffCall::operator()(double spot) const
{
    return max(spot - strike, 0.0);
}

PayOff *PayOffCall::clone() const
{
    return new PayOffCall(*this);
}

double PayOffPut::operator()(double spot) const
{
    return max(strike - spot, 0.0);
}

PayOffPut::PayOffPut(double strike_) : strike(strike_)
{
}

PayOff *PayOffPut::clone() const
{
    return new PayOffPut(*this);
}

PayOffCustomCall::PayOffCustomCall(double strike_)
{
    strike = strike_;
}

double PayOffCustomCall::operator()(double spot) const
{
    if (spot <= strike) return 0;
    else if (spot <= 1.05 * strike) return 1;
    else if (spot <= 1.10 * strike) return 2;
    else return 3;
}

PayOff *PayOffCustomCall::clone() const
{
    return new PayOffCustomCall(*this);
}

PayOffCustomPut::PayOffCustomPut(double strike_)
{
    strike = strike_;
}

double PayOffCustomPut::operator()(double spot) const
{
    if (spot >= strike) return 0;
    else if (spot >= 0.95 * strike) return 1;
    else if (spot >= 0.90 * strike) return 2;
    else return 3;
}

PayOff *PayOffCustomPut::clone() const
{
    return new PayOffCustomPut(*this);
}

