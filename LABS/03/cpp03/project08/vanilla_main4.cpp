#include "iostream"
#include "simple_mc6.h"
#include "vanilla3.h"

using namespace std;

int main()
{
    double expiry;
    double strike;
    double spot;
    double vol;
    double r;
    unsigned long number_of_paths;
    double strike2;

    cout << "\nEnter expiry\n";
    cin >> expiry;

    cout << "\nEnter strike\n";
    cin >> strike;

    cout << "\nEnter strike2 (K2, must be < strike)\n";
    cin >> strike2;

    cout << "\nEnter spot\n";
    cin >> spot;

    cout << "\nEnter vol\n";
    cin >> vol;

    cout << "\nEnter r\n";
    cin >> r;

    cout << "\nNumber of paths\n";
    cin >> number_of_paths;

    PayOffCall the_payoff(strike);
    VanillaOption option1(the_payoff, expiry);

    ParametersConstant vol_param(vol);
    ParametersConstant r_param(r);

    double result = simple_monte_carlo6(option1,
                                        spot,
                                        vol_param,
                                        r_param,
                                        number_of_paths);

    cout << "\nThe call price is " << result << "\n";

    VanillaOption option2(option1);

    result = simple_monte_carlo6(option2,
                                 spot,
                                 vol_param,
                                 r_param,
                                 number_of_paths);

    cout << "\nThe call price is " << result << "\n";

    PayOffPut the_payoff2(strike);
    // std::cout << "step 1\n";
    VanillaOption option3(the_payoff2, expiry);
    // std::cout << "step 2\n";
    option1 = option3;
    // std::cout << "step 3\n";

    result = simple_monte_carlo6(option1,
                                 spot,
                                 vol_param,
                                 r_param,
                                 number_of_paths);

    cout << "\nThe put price is " << result << "\n";

    PayOffBarrierCall levCall(strike, strike2);
    VanillaOption levCallOption(levCall, expiry);
    result = simple_monte_carlo6(levCallOption, spot, vol_param, r_param, number_of_paths);
    cout << "\nThe barrier call price is " << result << "\n";

    PayOffBarrierPut levPut(strike, strike2);
    VanillaOption levPutOption(levPut, expiry);
    result = simple_monte_carlo6(levPutOption, spot, vol_param, r_param, number_of_paths);
    cout << "\nThe barrier put price is " << result << "\n";

    return 0;
}
