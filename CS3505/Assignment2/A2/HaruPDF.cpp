/* Assignment 2 HaruPDF Class. Written by Tim Dorny u0829896.
 This class provides base functionality in building a PDF file*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "HaruPDF.h"

    // Creates the base pdf file.
    HaruPDF::HaruPDF(){
        // Initiallize PDF
        MainPdf = HPDF_New(NULL, NULL);
        // Create Page
        MainPage = HPDF_AddPage (MainPdf);
        // Format Page
        HPDF_Page_SetSize (MainPage, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
        MainFont = HPDF_GetFont (MainPdf, "Helvetica", NULL);
        HPDF_Page_SetTextLeading (MainPage, 20);
        HPDF_Page_SetGrayStroke (MainPage, 0);

        // Done with initiallization.
        // Begin Text/set font
        HPDF_Page_BeginText (MainPage);
        MainFont = HPDF_GetFont (MainPdf, "Helvetica", NULL);
        HPDF_Page_SetFontAndSize (MainPage, MainFont, 30);
    }

    // Places characters on the provided location on the pdf.
    void HaruPDF::PlaceCharacter(char text, double xPosition, double yPosition, double spiralAngle, double textAngle){

        //TESTING
        std::cout << text<< "\n";
        std::cout << xPosition << "\n";
        std::cout << yPosition << "\n";
        std::cout << spiralAngle << "\n";
        ///TESTING

        // Char array to write char to pdf.
        char txt[2];

        //TESTING
        HPDF_SaveToFile (MainPdf, "PlaceCharacterPDFGenTest1.pdf");

        // Convert angle to rads.
        double spiralRads = textAngle / (180 * M_PI);

        // Set text orientation on page. [HAVING ISSUES]
        HPDF_Page_SetTextMatrix(MainPage, cos(spiralRads), sin(spiralRads), -sin(spiralRads), cos(spiralRads), xPosition, yPosition);

        //TESTING
        HPDF_SaveToFile (MainPdf, "PlaceCharacterPDFGenTest2.pdf");

        // Place character to print into txt
        txt[0] = text;
        txt[1] = 0;

        //TESTING
        std::cout << "\n\n\n" << txt << "\n\n\n";

        // Write character to pdf page [HAVING ISSUES]
        HPDF_Page_ShowText (MainPage, txt);

        //TESTING
        HPDF_SaveToFile (MainPdf,"PlaceCharacterPostCharAddTest.pdf");


    }
    // Finalize PDF and save to file
    void HaruPDF::SavePdf(){

        const char * filename = "spiralPDF.pdf";
        //PdfName = "spiralPDF.pdf";
        HPDF_Page_EndText(MainPage);
        // Save to file
        HPDF_SaveToFile(MainPdf, filename);
        // Clean up
        HPDF_Free (MainPdf);

    }
