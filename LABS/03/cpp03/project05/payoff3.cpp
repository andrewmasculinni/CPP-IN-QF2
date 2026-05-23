// PayOff.cpp

#include "payoff3.h"
#include "minmax.h"

// definition of a constructor
PayOffCall::PayOffCall(double strike_)
{
    strike = strike_;
}

// definition of a function
double PayOffCall::operator()(double spot) const
{
    return max(spot - strike, 0.0);
}

// definition of a constructor
PayOffPut::PayOffPut(double strike_)
{
    strike = strike_;
}

// definition of a function
double PayOffPut::operator()(double spot) const
{
    return max(strike - spot, 0.0);
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