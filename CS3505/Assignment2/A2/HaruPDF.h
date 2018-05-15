#ifndef HARU_PDF_IS_FUN
#define HARU_PDF_IS_FUN

#include "hpdf.h"

class HaruPDF {
public:
    HPDF_Doc MainPdf;
    HPDF_Page MainPage;
    char* Text;
    char PdfName[256];
    HPDF_Font MainFont;

    HaruPDF();
    void PlaceCharacter(char text, double xPosition, double yPosition, double spiralAngle, double textAngle);
    void SavePdf();
};
#endif
