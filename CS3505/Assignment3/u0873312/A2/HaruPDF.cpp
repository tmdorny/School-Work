// A2: Classes and Facades
// Nick(Mykola) Pershyn
// CS3505 (CS5020)

#include <cmath>
#include "HaruPDF.h"


HaruPDF::HaruPDF()
{
	pdf = HPDF_New (NULL, NULL);
	return;
}

HaruPDF::~HaruPDF()
{
	// clean up
	HPDF_Free (pdf);
	return;
}

void HaruPDF::startNewPage()
{
	// add a new page object.
	page = HPDF_AddPage (pdf);
	HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);

	//    print_grid  (pdf, page);
	font = HPDF_GetFont (pdf, "Helvetica", NULL);
	HPDF_Page_SetTextLeading (page, 20);
	HPDF_Page_SetGrayStroke (page, 0);
	
	HPDF_Page_BeginText (page);
	font = HPDF_GetFont (pdf, "Courier-Bold", NULL);
	HPDF_Page_SetFontAndSize (page, font, 30);
	return;
}

void HaruPDF::writeCharAtPosition(const char symbol, float x, float y, float angle)
{
	angle *= M_PI;
	angle /= 180;
	char buf[2] = {symbol,0};
	HPDF_Page_SetTextMatrix(page, cos(angle), sin(angle), -sin(angle), cos(angle), x, y);
	HPDF_Page_ShowText (page, buf);
	return;
}

void HaruPDF::finnishPage()
{
	HPDF_Page_EndText (page);
	return;
}

void HaruPDF::saveFile(const std::string& fname)
{
	// save the document to a file
	HPDF_SaveToFile (pdf, fname.c_str());
	return;
}