#include "normdist.h"
#include <iostream>
#include <cmath>
#include "simple_mc2.h"
using namespace std;

struct OptionData
{
    double strike;
    double spot;
    double r;
    double vol;
    double expiry;
    int type; // 0 call, 1 put
};

// Function to print option data by value
void printOption(OptionData opt)
{
    cout << "Strike: " << opt.strike << "\n";
    cout << "Spot: " << opt.spot << "\n";
    cout << "Risk-free rate: " << opt.r << "\n";
    cout << "Volatility: " << opt.vol << "\n";
    cout << "Expiry: " << opt.expiry << "\n";
    cout << "Type: " << (opt.type == 0 ? "call" : "put") << "\n";
}

// Function to print option data by pointer
void printOptionPtr(OptionData* opt)
{
    cout << "Strike: " << opt->strike << "\n";
    cout << "Spot: " << opt->spot << "\n";
    cout << "Risk-free rate: " << opt->r << "\n";
    cout << "Volatility: " << opt->vol << "\n";
    cout << "Expiry: " << opt->expiry << "\n";
    cout << "Type: " << (opt->type == 0 ? "call" : "put") << "\n";
}

// Function to print option data by reference
void printOptionRef(OptionData& opt)
{
    cout << "Strike: " << opt.strike << "\n";
    cout << "Spot: " << opt.spot << "\n";
    cout << "Risk-free rate: " << opt.r << "\n";
    cout << "Volatility: " << opt.vol << "\n";
    cout << "Expiry: " << opt.expiry << "\n";
    cout << "Type: " << (opt.type == 0 ? "call" : "put") << "\n";
}

// BS price by value
double bsPrice(OptionData opt)
{
    double t = sqrt(opt.expiry);
    double d1 = (log(opt.spot/opt.strike) + opt.r*opt.expiry)/(opt.vol*t) + 0.5*opt.vol*t;
    double d2 = d1 - opt.vol*t;
    if (opt.type == 0)
        return opt.spot*N(d1) - opt.strike*exp(-opt.r*opt.expiry)*N(d2);
    else
        return opt.strike*exp(-opt.r*opt.expiry)*N(-d2) - opt.spot*N(-d1);
}

// BS price by pointer
double bsPricePtr(OptionData* opt)
{
    double t = sqrt(opt->expiry);
    double d1 = (log(opt->spot/opt->strike) + opt->r*opt->expiry)/(opt->vol*t) + 0.5*opt->vol*t;
    double d2 = d1 - opt->vol*t;
    if (opt->type == 0)
        return opt->spot*N(d1) - opt->strike*exp(-opt->r*opt->expiry)*N(d2);
    else
        return opt->strike*exp(-opt->r*opt->expiry)*N(-d2) - opt->spot*N(-d1);
}

// BS price by reference
double bsPriceRef(OptionData& opt)
{
    double t = sqrt(opt.expiry);
    double d1 = (log(opt.spot/opt.strike) + opt.r*opt.expiry)/(opt.vol*t) + 0.5*opt.vol*t;
    double d2 = d1 - opt.vol*t;
    if (opt.type == 0)
        return opt.spot*N(d1) - opt.strike*exp(-opt.r*opt.expiry)*N(d2);
    else
        return opt.strike*exp(-opt.r*opt.expiry)*N(-d2) - opt.spot*N(-d1);
}

// MC price by value
double mcPrice(OptionData opt)
{
    if (opt.type == 0)
    {
        PayOffCall payoff(opt.strike);
        return simple_monte_carlo2(payoff, opt.expiry, opt.spot, opt.vol, opt.r, 100000);
    }
    else
    {
        PayOffPut payoff(opt.strike);
        return simple_monte_carlo2(payoff, opt.expiry, opt.spot, opt.vol, opt.r, 100000);
    }
}

// MC price by pointer
double mcPricePtr(OptionData* opt)
{
    if (opt->type == 0)
    {
        PayOffCall payoff(opt->strike);
        return simple_monte_carlo2(payoff, opt->expiry, opt->spot, opt->vol, opt->r, 100000);
    }
    else
    {
        PayOffPut payoff(opt->strike);
        return simple_monte_carlo2(payoff, opt->expiry, opt->spot, opt->vol, opt->r, 100000);
    }
}

// MC price by reference
double mcPriceRef(OptionData& opt)
{
    if (opt.type == 0)
    {
        PayOffCall payoff(opt.strike);
        return simple_monte_carlo2(payoff, opt.expiry, opt.spot, opt.vol, opt.r, 100000);
    }
    else
    {
        PayOffPut payoff(opt.strike);
        return simple_monte_carlo2(payoff, opt.expiry, opt.spot, opt.vol, opt.r, 100000);
    }
}

int main()
{
    // Create an instance and assign values
    OptionData opt;
    opt.strike = 100;
    opt.spot = 90;
    opt.r = 0.05;
    opt.vol = 0.2;
    opt.expiry = 1;
    opt.type = 0;

    cout << "\nBy value:\n";
    printOption(opt);

    // Create a pointer to the structure
    OptionData* optPtr = &opt;
    cout << "\nAddress: " << optPtr << "\n";

    cout << "\nBy pointer:\n";
    printOptionPtr(optPtr);

    cout << "\nBy reference:\n";
    printOptionRef(opt);

    cout << "\nBS price by value: " << bsPrice(opt) << "\n";
    cout << "BS price by pointer: " << bsPricePtr(optPtr) << "\n";
    cout << "BS price by reference: " << bsPriceRef(opt) << "\n";

    cout << "\nMC price by value: " << mcPrice(opt) << "\n";
    cout << "MC price by pointer: " << mcPricePtr(optPtr) << "\n";
    cout << "MC price by reference: " << mcPriceRef(opt) << "\n";

    return 0;
}