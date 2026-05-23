#include <iostream>
#include <fstream>
#include "simple_mc3.h"
#include "double_digital.h"
#include "vanilla1.h"
#include "payoff3.h"

using namespace std;

int main()
{
	double expiry;
	double low, up;
	double spot;
	double vol;
	double r;
	unsigned long number_of_paths;

	cout << "\nEnter expiry\n";
	cin >> expiry;

	cout << "\nEnter lower strike\n";
	cin >> low;

	cout << "\nEnter upper strike\n";
	cin >> up;

	cout << "\nEnter spot\n";
	cin >> spot;

	cout << "\nEnter vol\n";
	cin >> vol;

	cout << "\nEnter r\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> number_of_paths;

	PayOffDoubleDigital thePayOff(low, up);
	// PayOffPut thePayOff(low);

	PayOffCustomCall customCall(low);
    PayOffCustomPut customPut(low);

    VanillaOption customCallOption(customCall, expiry);
    VanillaOption customPutOption(customPut, expiry);

    double resultCustomCall = SimpleMonteCarlo3(customCallOption, spot, vol, r, number_of_paths);
    double resultCustomPut = SimpleMonteCarlo3(customPutOption, spot, vol, r, number_of_paths);

    cout << "\nCustom call price: " << resultCustomCall << "\n";
    cout << "Custom put price: " << resultCustomPut << "\n";


	VanillaOption theOption(thePayOff, expiry);

	double result = SimpleMonteCarlo3(theOption,
									  spot,
									  vol,
									  r,
									  number_of_paths);

	cout << "\nthe price is " << result << "\n";

	unsigned int nReps = 1000;
	double prices[nReps];
	for (unsigned int i = 0; i < nReps; ++i)
	{
		prices[i] = SimpleMonteCarlo3(theOption,
									  spot,
									  vol,
									  r,
									  number_of_paths);
	}

	std::ofstream outFile("output.csv");

	// Step 3: Check if file opened successfully
	if (!outFile)
	{
		std::cerr << "Error: Could not open the file for writing.\n";
		return 1; // Exit with error code
	}

	// Step 4: Write each element of the vector to a new line in the file
	for (double value : prices)
	{
		outFile << value << "\n";
	}

	// Step 5: Close the file
	outFile.close();

	std::cout << "Data successfully written to output.csv\n";

	return 0;
}
