// simple_mc_main2.cpp

#include "simple_mc.h"
#include <iostream>
using namespace std;

int main()
{
	double expiry;
	double strike;
	double spot;
	double vol;
	double r;
	unsigned long number_of_paths;
	double strike_upper;

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

	cout << "\nNumber of paths\n";
	cin >> number_of_paths;
	cout << "\nEnter upper strike\n";
	cin >> strike_upper;


	Payoff call_payoff(strike, Payoff::Call);
	Payoff put_payoff(strike, Payoff::Put);
	Payoff call_squared_payoff(strike, Payoff::CallSquaredPower);
	Payoff put_squared_payoff(strike, Payoff::PutSquaredPower);
	Payoff call_power(strike, Payoff::CallPower);
	Payoff put_power(strike, Payoff::PutPower);
	Payoff digital(strike, Payoff::Digital);
	Payoff double_digital(strike, strike_upper, Payoff::DoubleDigital);



	double result_call = simple_monte_carlo(call_payoff,
											expiry,
											spot,
											vol,
											r,
											number_of_paths);

	double result_put = simple_monte_carlo(put_payoff,
										   expiry,
										   spot,
										   vol,
										   r,
										   number_of_paths);

	double result_call_squared = simple_monte_carlo(call_squared_payoff, 
													expiry, 
													spot, 
													vol, 
													r, 
													number_of_paths);
												
	double result_put_squared = simple_monte_carlo(put_squared_payoff, 
												   expiry, 
												   spot, 
												   vol, 
												   r, 
												   number_of_paths);

	double result_call_power = simple_monte_carlo(call_power, 
													expiry, 
													spot, 
													vol, 
													r, 
													number_of_paths);
	double result_put_power = simple_monte_carlo(put_power, 
												 expiry, 
												 spot, 
												 vol, 
												 r, 
												 number_of_paths);

	double result_digital = simple_monte_carlo(digital, 
											   expiry, 
											   spot, 
											   vol, 
											   r, 
											   number_of_paths);

	double result_double_digital = simple_monte_carlo(double_digital, 
													  expiry, 
													  spot, 
													  vol, 
													  r, 
													  number_of_paths);


	cout << "\nthe prices are:\n"
		 << result_call << " for the call\n"
		 << result_put << " for the put\n"
		 << result_call_squared << " for he squared power call\n"
		 << result_put_squared << " for the squared power put\n"
		 << result_call_power << " for the power call\n"
		 << result_put_power << " for the power put\n"
		 << result_digital << " for the digital\n"
		 << result_double_digital << " for the double digital\n";



	double tmp;
	cin >> tmp;

	return 0;
}
