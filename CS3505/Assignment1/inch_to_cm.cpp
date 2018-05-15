// Assignment 1 by Tim Dorny, u0829896
// This program takes input from the user, and converts the provided values
// from inches to centimeters using 2 decimal fixed precision.

#include <iostream>
#include <iomanip>

// Converts and int from inches to centimeters in double format.
double convertInchToCm (int inch){
    double centimeters = inch * 2.54;
    return centimeters;
}
// Outputs a double with 2 decimal fixed position followed by a newline.
void niceOutput(double cm){

    std::cout << std::fixed << std::setprecision(30);
    std::cout << 0.3 << "\n";
        return;
}

int main(){
    int input;
    // Loop that handles user input. Ctrl+D == EoF
    // Input is expected to be valid integers separated by whitespace.
    while (std::cin >> input){

        // Converts provided integer from inches to centimeters.
        double inputCm = convertInchToCm(input);
        // Outputs the resulting conversion.
        niceOutput(inputCm);
    }
}
