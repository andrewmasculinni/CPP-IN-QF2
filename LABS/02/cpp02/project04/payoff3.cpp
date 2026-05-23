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

PayOffDigital::PayOffDigital(double strike_)
{
    strike = strike_;
}

double PayOffDigital::operator()(double spot) const
{
    return (spot > strike) ? 1.0 : 0.0;
}

PayOffDoubleDigital::PayOffDoubleDigital(double strike_, double strike_upper_)
{
	strike = strike_;
	strike_upper = strike_upper_;
}

double PayOffDoubleDigital::operator()(double spot) const
{
	return (spot > strike && spot < strike_upper) ? 1.0 : 0.0;
}

PayOffPower1::PayOffPower1(double strike_, int type_)
{
	strike = strike_;
	type = type_;
}

double PayOffPower1::operator()(double spot) const
{
	if (type == 0)
		return max(spot - strike, 0.0) * max(spot - strike, 0.0);
	else
		return max(strike - spot, 0.0) * max(strike - spot, 0.0);
}

PayOffPower2::PayOffPower2(double strike_, int type_)
{
	strike = strike_;
	type = type_;
}

double PayOffPower2::operator()(double spot) const
{
	if (type == 0)
		return max(spot*spot - strike*strike, 0.0);
	else
		return max(strike*strike - spot*spot, 0.0);
}

