// simple_mc_main1.cpp
// requires random1.cpp

#include "random1.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// main function
int main()
{

	srand(time(NULL));
	double expiry;
	double strike;
	double spot;
	double vol;
	double r;
	unsigned long number_of_paths;
	double strike_upper;

	std::cout << "\nEnter expiry\n";
	std::cin >> expiry;

	std::cout << "\nEnter strike\n";
	std::cin >> strike;

	std::cout << "\nEnter an upper strike\n";
	std::cin >> strike_upper;

	std::cout << "\nEnter spot\n";
	std::cin >> spot;

	std::cout << "\nEnter volatility\n";
	std::cin >> vol;

	std::cout << "\nEnter risk-free rate\n";
	std::cin >> r;

	std::cout << "\nNumber of paths\n";
	std::cin >> number_of_paths;

	double variance = vol * vol * expiry;
	double root_variance = sqrt(variance);
	double ito_correction = -0.5 * variance;
	double moved_spot = spot * exp(r * expiry + ito_correction);

	double running_sum_call = 0;
	double running_sum_put = 0;
	double running_sum_digital = 0;
	double running_sum_ddigital = 0;

	for (unsigned long i = 0; i < number_of_paths; i++)
	{
		double this_gaussian = get_one_gaussian_by_box_muller();
		double this_spot = moved_spot * exp(root_variance * this_gaussian);

		running_sum_call += (this_spot - strike > 0) ? (this_spot - strike) : 0;
		running_sum_put += (strike - this_spot > 0) ? (strike - this_spot) : 0;

		// Digital option
		running_sum_digital += (this_spot > strike) ? 1.0 : 0.0;

		// Double digital option with two strikes- lower and upper
		running_sum_ddigital += (this_spot > strike && this_spot < strike_upper) ? 1.0 : 0.0;
	}

	double discount = exp(-r * expiry);
	std::cout << "European call:" << running_sum_call / number_of_paths * discount << "\n";
	std::cout << "European put:" << running_sum_put/ number_of_paths * discount << "\n";
	std::cout << "Digital:" << running_sum_digital / number_of_paths * discount << "\n";
	std::cout << "Double digital:" << running_sum_ddigital / number_of_paths * discount << "\n";


	double tmp;
	std::cin >> tmp;

	return 0;
}