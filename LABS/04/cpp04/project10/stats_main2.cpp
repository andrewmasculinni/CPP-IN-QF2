#include <iostream>
#include "simple_mc7.h"
#include "vanilla3.h"
#include "statistics_mc.h"
#include "convergence_table.h"
#include "random1.h"
#include <cmath>

using namespace std;

int main()
{
    double expiry = 0.5;
    double strike = 100.0;
    double spot = 95.0;
    double vol = 0.2;
    double r = 0.06;
    unsigned long number_of_paths = 1000000;

    cout << "Do you want to enter your own option paramters (1) or use defaults (2)?\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nEnter expiry\n";
        cin >> expiry;

        cout << "\nEnter strike\n";
        cin >> strike;

        cout << "\nEnter spot\n";
        cin >> spot;

        cout << "\nEnter vol\n";
        cin >> vol;

        cout << "\nEnter r\n";
        cin >> r;

        cout << "\nEnter number of paths\n";
        cin >> number_of_paths;
    }

    PayOffCall thePayOff(strike);

    VanillaOption the_option(thePayOff, expiry);

    ParametersConstant vol_param(vol);
    ParametersConstant r_param(r);

    StatisticsMean gathererMean;
    StatisticsSD gathererSD;
    ConvergenceTable gatherer_two(gathererMean);
    ConvergenceTable gatherer_three(gathererSD);

    simple_monte_carlo7(the_option,
                        spot,
                        vol_param,
                        r_param,
                        number_of_paths,
                        gatherer_two);
    
    simple_monte_carlo7(the_option, 
                        spot, 
                        vol_param, 
                        r_param, 
                        number_of_paths, 
                        gatherer_three);
    vector<vector<double>> results = gatherer_two.get_results_so_far();
    cout << "\nFor the call price the results are \n";

    for (unsigned long i = 0; i < results.size(); i++)
    {
        for (unsigned long j = 0; j < results[i].size(); j++)
        {
            cout << results[i][j] << " ";
        }
        cout << "\n";
    }

    vector<vector<double>> resultsSD = gatherer_three.get_results_so_far();
    cout << "\nSD convergence table (mean, sd, ci_low, ci_high, paths)\n";
    for (unsigned long i = 0; i < resultsSD.size(); i++)
    {
        for (unsigned long j = 0; j < resultsSD[i].size(); j++)
        {
            cout << resultsSD[i][j] << " ";
        }
        cout << "\n";
    }

    double desired_precision;
    cout << "\nEnter desired precision\n";
    cin >> desired_precision;

    double expiry_val = the_option.get_expiry();
    double var = vol_param.get_integral_square(0, expiry_val);
    double root_var = sqrt(var);
    double ito_corr = -0.5 * var;
    double moved_spot = spot * exp(r_param.get_integral(0, expiry_val) + ito_corr);
    double disc = exp(-r_param.get_integral(0, expiry_val));

    StatisticsSD early_gatherer;
    unsigned long stop_point = 2;
    unsigned long done = 0;

    cout << "\nEarly stopping convergence (mean, sd, ci_low, ci_high, paths)\n";
    for (unsigned long i = 0; i < number_of_paths; i++)
    {
        double g = get_one_gaussian_by_box_muller();
        double s = moved_spot * exp(root_var * g);
        early_gatherer.dump_one_result(the_option.get_option_payoff(s) * disc);
        done++;

        if (done == stop_point)
        {
            stop_point *= 2;
            vector<vector<double>> r = early_gatherer.get_results_so_far();
            for (unsigned long j = 0; j < r[0].size(); j++)
                cout << r[0][j] << " ";
            cout << done << "\n";

            if (r[0][1] > 0 && r[0][1] < desired_precision)
            {
                cout << "Stopped at " << done << " paths\n";
                break;
            }
        }
    }

    return 0;
}
