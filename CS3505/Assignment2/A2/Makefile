# Compiler and flags.
CC = g++
CFLAGS = -Wall -std=c++11
LIBHARU = ../libharu
spiralPDF : spiralPDF.cpp HaruPDF.o Spiral.o
	$(CC) $(CFLAGS) -o spiralPDF spiralPDF.cpp HaruPDF.o Spiral.o -L$(LIBHARU)/src/ -I$(LIBHARU)/include -lhpdfs -lz

HaruPDF.o : HaruPDF.h HaruPDF.cpp
	$(CC) $(CFLAGS) -c HaruPDF.cpp -L$(LIBHARU)/src/ -I$(LIBHARU)/include -lhpdfs -lz

Spiral.o : Spiral.h Spiral.cpp
	$(CC) $(CFLAGS) -c Spiral.cpp

# Clean and Test
clean : 
	rm spiralPDF *.o

test :
	./spiralPDF "this is a test string that won't get written to a pdf because c++ hurts my soul."
