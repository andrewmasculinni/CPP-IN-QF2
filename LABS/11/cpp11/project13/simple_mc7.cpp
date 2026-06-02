#include <cmath>
#include "simple_mc7.h"
#include "random1.h"
#include <iostream>
#include "terminator.h"

using namespace std;

void simple_monte_carlo7b(const VanillaOption &the_option,
						  double spot,
						  const Parameters &vol,
						  const Parameters &r,
						  unsigned long number_of_paths,
						  Terminator &gatherer)
{
	double expiry = the_option.get_expiry();
	double variance = vol.get_integral_square(0, expiry);
	double root_variance = sqrt(variance);
	double ito_correction = -0.5 * variance;
	double moved_spot = spot * exp(r.get_integral(0, expiry) + ito_correction);
	double this_spot = 0.0;
	double discounting = exp(-r.get_integral(0, expiry));

	bool converged = false;
	double startTime = time(NULL);
	unsigned long i = 0;

	while (converged == false && i < number_of_paths)
	{
		i++;
		double this_gaussian = get_one_gaussian_by_box_muller();
		this_spot = moved_spot * exp(root_variance * this_gaussian);
		double thisPayOff = the_option.get_option_payoff(this_spot);
		gatherer.dump_one_result(thisPayOff * discounting);
		converged = gatherer.converged();
		if ((i % 10000) == 0)
		{
			std::cout << i << " " << gatherer.get_current_stddev() << " " << double(time(NULL)) - startTime << "\n";
		}
	}
}
