/*  Assignment 2 Spiral PDF Class. Written by Tim Dorny u0829896
 This class creates a pdf with text displayed in a spiral pattern.*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include "HaruPDF.h"
#include "Spiral.h"
//#include "hpdf.h"

int main (int argc, char **argv){

    // Initaillize array to hold incoming text.
    char Text[256];

    // Create PDF
    HaruPDF pdf = HaruPDF();
    // Copy input text to 'Text'
    strcpy (Text, argv[1]);

    //TESTING
    std::cout << Text;

    // Create spiral.
    Spiral spiralGen = Spiral(50, 50);

    // Loop to add characters to pdf.
    for (unsigned int i = 0; i < strlen(Text); i++){

        // Call pdf method to add each char to pdf using spiral coords.
        pdf.PlaceCharacter(Text[i], spiralGen.get_text_x(), spiralGen.get_text_y(), spiralGen.get_spiral_angle(), spiralGen.get_text_angle());

        //TESTING
        HPDF_SaveToFile (pdf.MainPdf, "PreSpiralUpdateTest.pdf");

        // Move spiral to next valid location.
        spiralGen++;

        //TESTING
        HPDF_SaveToFile (pdf.MainPdf, "PostSpiralUpdateTest.pdf");
    }
    //TESTING
    HPDF_SaveToFile (pdf.MainPdf, "PostCharacterPlacementTest.pdf");

    // Save PDF to file.
    pdf.SavePdf();

}
