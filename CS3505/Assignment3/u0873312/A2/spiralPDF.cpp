// A2: Classes and Facades
// Nick(Mykola) Pershyn
// CS3505 (CS5020)
#include <iostream>
#include <cmath>

#include "HaruPDF.h"
#include "Spiral.h"


void writeSpiralTextToCurrentPage(const std::string& text, HaruPDF& pdf, Spiral& spiral)
{

	for (unsigned int i = 0; i < text.size(); i++)
	{
		pdf.writeCharAtPosition(text[i], spiral.get_text_x(), spiral.get_text_y(), spiral.get_text_angle());
		spiral++;
	}
	
	return;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Give me some text as a parameter next time!" << std::endl;
		std::cout << "There is nothing for me to do, so I am quitting now..." << std::endl;
		return 0;
	}
	// argv are the command line arguments
	// argv[0] is the name of the executable program
	std::string fileName(std::string(argv[0]) + ".pdf");

	// text along a spiral
	std::string my_text(argv[1]);
	
	const float x0 = 210;
	const float y0 = 300;
	const float angle2 = 90;
	const float r = 10;

	Spiral my_spiral(x0, y0, angle2, r);
	//std::cout << my_spiral << std::endl;


	HaruPDF my_pdf;
	my_pdf.startNewPage();
	writeSpiralTextToCurrentPage(my_text, my_pdf, my_spiral);
	my_pdf.finnishPage();
	my_pdf.saveFile(fileName);
	//std::cout << my_spiral << std::endl;
	

	return 0;
}
