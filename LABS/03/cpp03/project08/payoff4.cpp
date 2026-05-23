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

PayOffBarrierCall::PayOffBarrierCall(double strike1_, double strike2_)
{
    strike1 = strike1_;
    strike2 = strike2_;
}

double PayOffBarrierCall::operator()(double spot) const
{
    if (spot <= strike2)
        return max(spot - strike1, 0.0);
    else
        return 2 * max(spot - strike1, 0.0);
}

PayOffBarrierPut::PayOffBarrierPut(double strike1_, double strike2_)
{
    strike1 = strike1_;
    strike2 = strike2_;
}

double PayOffBarrierPut::operator()(double spot) const
{
    if (spot > strike1)
        return max(strike2 - spot, 0.0);
    else
        return 2 * max(strike2 - spot, 0.0);
}

PayOff *PayOffBarrierCall::clone() const
{
    return new PayOffBarrierCall(*this);
}

PayOff *PayOffBarrierPut::clone() const
{
    return new PayOffBarrierPut(*this);
}