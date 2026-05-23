// payoff1.h

#ifndef PAYOFF1_H
#define PAYOFF1_H

class Payoff
{

public:
    enum OptionType
    {
        Call,
        Put,
        CallSquaredPower,
        PutSquaredPower,
        CallPower,
        PutPower,
        Digital,
        DoubleDigital
    };

    Payoff(double strike, OptionType option_type);
    // Double digital option
    Payoff(double strike, double strike_upper, OptionType option_type);


    double operator()(double spot) const;

private:
    double strike_;
    double strike_upper_;
    OptionType option_type_;
};

#endif
