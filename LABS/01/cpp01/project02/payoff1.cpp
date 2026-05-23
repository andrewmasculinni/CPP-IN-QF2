// payoff1.cpp

#include "payoff1.h"
#include "min_max.h"

Payoff::Payoff(double strike, OptionType option_type)
    : strike_(strike), option_type_(option_type)
{
}

double Payoff::operator()(double spot) const
{
    switch (option_type_)
    {
    case Call:
        return max(spot - strike_, 0.0);

    case Put:
        return max(strike_ - spot, 0.0);

    case CallSquaredPower:
        return max(spot - strike_, 0.0) * max(spot - strike_, 0.0);

    case PutSquaredPower:
        return max(strike_ - spot, 0.0) * max(strike_ - spot, 0.0);

    case CallPower:
        return max(spot*spot - strike_*strike_, 0.0);

    case PutPower:
        return max(strike_*strike_ - spot*spot, 0.0);

    case Digital:
        return (spot > strike_) ? 1.0 : 0.0;
    
    case DoubleDigital:
        return (spot > strike_ && spot < strike_upper_) ? 1.0 : 0.0;


    default:
        throw("Unknown option type found.");
    }
}

Payoff::Payoff(double strike, double strike_upper, OptionType option_type)
    : strike_(strike), strike_upper_(strike_upper), option_type_(option_type)
{
}

