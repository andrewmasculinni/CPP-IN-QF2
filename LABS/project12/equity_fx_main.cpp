#include <iostream>
#include "park_miller.h"
#include "statistics_mc.h"
#include "convergence_table.h"
#include "antithetic.h"
#include "path_dependent_asian.h"
#include "path_dependent_geometric_asian.h"
#include "path_dependent_european.h"
#include "exotic_bs_engine.h"
#include "path_dependent_barrier_asian_straddle.h"
#include "conf_limits.h"
#include <fstream>

using namespace std;

int main()
{
    // We first declare variables and ask the user to provide them.
    double expiry;
    double strike;
    double spot;
    double vol;
    double r;
    double d;
    double b_upper;
    double b_lower;
    unsigned long int number_of_paths;
    unsigned long int number_of_dates;

    short unsigned decision = 2;
    while (decision > 1)
    {
        cout << "Do you want to take default parameters (0) or provide your own (1)?\n";
        cin >> decision;
    }

    if (decision == 0)
    {
        expiry = 0.5;
        strike = 100;
        spot = 95;
        vol = 0.2;
        r = 0.06;
        d = 0.0;
        b_upper = 125;
        b_lower = 90;
        number_of_paths = 100000;
        number_of_dates = 252 * expiry;
    }
    else
    {
        cout << "\nEnter expiry\n";
        cin >> expiry;

        cout << "\nEnter strike\n";
        cin >> strike;

        cout << "\nEnter spot\n";
        cin >> spot;

        cout << "\nEnter volatility\n";
        cin >> vol;

        cout << "\nEnter risk-free rate\n";
        cin >> r;

        cout << "\nEnter dividend rate\n";
        cin >> d;

        cout << "\nEnter upper barrier\n";
        cin >> b_upper;

        cout << "\nEnter lower barrier\n";
        cin >> b_lower;


        cout << "\nEnter number of intervals\n";
        cin >> number_of_dates;

        cout << "\nEnter number of paths\n";
        cin >> number_of_paths;
    }

    // Create an object of PayOffCall type.
    PayOffCall the_payoff(strike);

    // Create an array (an object of type MJArray) which will store
    // time index for each date (interval).
    MJArray times(number_of_dates);
    for (unsigned long i = 0; i < number_of_dates; i++)
    {
        times[i] = (i + 1.0) * expiry / number_of_dates;
    }
    // Note, that for daily intervals expiry/number_of_dates should equal to 1/252.

    // Create constant volatility, risk-free rate and dividend rate parameters
    // (these are objects of already well known ParametersConstant class).
    ParametersConstant vol_param(vol);
    ParametersConstant r_param(r);
    ParametersConstant d_param(d);

    // Create the product, ie. an object of the PathDependentAsian class.
    // This class inherits after the PathDependent base class.
    // Note, that one of the arguments of the constructor is thePayOff,
    // ie. the object of the PayOffCall class.
    PathDependentBarrierAsianStraddle the_option(times, expiry, strike, b_upper, b_lower);

    // Create the object of the StatisticsMean class
    // responsible for calculating the mean discounted pay-off.
    // Note, that the StatisticsMean class inherits after StatisticsMC base class.
    StatisticsMean gatherer;

    // Create an object of the ConvergenceTable.
    // We use here the decoration pattern: gatherer2 can take the gatherer as argument
    // and store it as its data member. This trick is called 'the decoration pattern'.
    // Note, that the ConvergenceTable class also inherits after StatisticsMC base class.
    ConvergenceTable gatherer2(gatherer);
    ConfidenceLimits gatherer_ci;

    // Create an object of the RandomParkMiller class, responsible for drawing normal variates.
    // RandomParkMiller inherits after RandomBase base class.
    // numberOfDates serves as dimensionality, for example: for expiry = 0.5 we have 126 days to maturity,
    // and this means, that for each of 126 we have to simulate increment, ie. draw a single gaussian variate.
    // The second argument (seed) is missing here, 
    // as it has a default value.
    RandomParkMiller generator(number_of_dates, 1);

    // Create an object of the AntiThetic class.
    // AntiThetic class also inherits after the RandomBase class.
    // generator2 can take generator as its argument and store it as its data member.
    AntiThetic generator2(generator);

    // Create our ENGINE: an object of the ExoticBSEngine. This class inherits after the ExoticEngine base class
    // and is responsible for simulating the single paths of underlying prices, according to the
    // Black-Scholes assumptions, ie. under geometric Brownian motion
    // Having created theEngine, we put into it:
    // 1) the product, ie. the specific (path-dependent) option, with defined payoff function
    // 2) three (constant) stochastic process parameters
    // 3) pseudo-random numbers generator, decorated with the Antithetic subclass
    // 4) spot price of the underlying (at the moment of pricing)
    ExoticBSEngine the_engine(the_option, r_param, d_param, vol_param, generator2, spot);

    // Run OUR ENGINE: call the doSimulation() method of theEngine (i.e the object of the ExoticBSEngine subclass)
    // This method does the job of the SimpleMonteCarlo() method, ie. performs looping.
    // It needs to know: which statistics gatherer to use and how many times to loop.
    the_engine.do_simulation(gatherer2, number_of_paths);
    ExoticBSEngine the_engine2(the_option, r_param, d_param, vol_param, generator2, spot);
    the_engine2.do_simulation(gatherer_ci, number_of_paths);

    // We gather the results, ie. the convergence table after the desired number of loops
    // into results of type 'vector of vector of doubles'.
    vector<vector<double>> results = gatherer2.get_results_so_far();

    // Finally, we print out the results to the console.
    cout << "\nFor the barrier Asian straddle price the results are \n";


    for (unsigned long i = 0; i < results.size(); i++)
    {
        for (unsigned long j = 0; j < results[i].size(); j++)
            cout << results[i][j] << " ";
        cout << "\n";
    }

    vector<vector<double>> ci_results = gatherer_ci.get_results_so_far();
    cout << "\n90% confidence interval: [" << ci_results[2][0] << ", " << ci_results[2][1] << "]\n";
    cout << "Mean: " << ci_results[0][0] << "\n";

    ofstream csv_file("payoffs.csv");
    vector<double> payoffs = gatherer_ci.get_payoffs();
    csv_file << "payoff\n";
    for (unsigned long i = 0; i < payoffs.size(); i++)
        csv_file << payoffs[i] << "\n";
    csv_file.close();
    cout << "\nPayoffs written to payoffs.csv\n";

    return 0;
}
