// A2: Classes and Facades
// Nick(Mykola) Pershyn
// CS3505 (CS5020)

#pragma once
#include <string>
#include "hpdf.h"


class HaruPDF
{
private:
	HPDF_Doc  pdf;
	HPDF_Page page;
	HPDF_Font font;
public:
	HaruPDF();
	~HaruPDF();
	
	void startNewPage();
	void writeCharAtPosition(const char symbol, float x, float y, float angle);
	void finnishPage();
	
	void saveFile(const std::string& fname);
};

