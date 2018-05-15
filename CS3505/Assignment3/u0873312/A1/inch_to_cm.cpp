/* This is the first Homework
 * done by Nick(Mykola) Pershyn
 * This program gets numbers from standard input, converts them to cm
 * and prints them to standard output with giver precision.
 */

/* Usage for redirecting input and output:
 * ./inch_to_cm < input_file > output_file
 */

#include <iostream>
#include <iomanip>

void niceOutput(double cms);
double convertInchToCm(double number_of_inches);


// This function converts inches to cm
double convertInchToCm(double number_of_inches)
{
	// 2.54 - number of cm in one inch
	return number_of_inches * 2.54;
}

void niceOutput(double cms)
{
	std::cout << std::fixed << std::setprecision(2);
	std::cout << cms << std::endl << std::flush;
	return;
}


int main(int argc, char* argv[])
{
	double inches;
	while(std::cin >> inches)
	{
		niceOutput(convertInchToCm(inches));
	}
	
	// Easy way to check internal binary representation of 0.3
	//std::cerr << std::fixed << std::setprecision(30) << 0.3 << std::endl;
	//std::cerr << std::fixed << std::setprecision(30) << 0.3 * 256 * 256 * 256 * 256 * 256 * 256 * 64 << std::endl;
	
	return 0;
}