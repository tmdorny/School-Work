# A2: Classes and Facades
# Nick(Mykola) Pershyn
# CS3505 (CS5020)
 
CC = g++
OPTS = -Wall -std=c++11 -O2
PROGS = pdfExample spiralPDF

# Haru pdf library folder location
LIBHARU = ../libharu-libharu-d84867e

# header locations
# This option has been deprecated. Please use -iquote instead for -I directories before the -I- and remove the -I- option.
INCLUDE = -I$(LIBHARU)/include

# "-lhpdfs" for libhpdfs.a
# "-lz" to fix all errors like "undefined reference to `deflateInit_'"
LIBRARY = -lhpdfs -lz

# .so and .a file locations
DIRECTORY = -L$(LIBHARU)/src

OBJS = HaruPDF.o Spiral.o

# I want to make all the programms when I execute "make"
all: $(PROGS)

pdfExample:
	$(CC) $(OPTS)    -o pdfExample pdfExample.cpp $(INCLUDE) $(DIRECTORY) $(LIBRARY)

spiralPDF: $(OBJS)
	$(CC) $(OPTS)    -o spiralPDF  spiralPDF.cpp $(OBJS) $(INCLUDE) $(DIRECTORY) $(LIBRARY) 
	
HaruPDF.o:
	$(CC) $(OPTS) -c -o HaruPDF.o  HaruPDF.cpp    $(INCLUDE) $(DIRECTORY) $(LIBRARY)

Spiral.o:
	$(CC) $(OPTS) -c -o Spiral.o   Spiral.cpp     $(INCLUDE) $(DIRECTORY) $(LIBRARY)


clean:
	rm -f *.o $(PROGS)

test:
	./spiralPDF "This is my sample text"
failtest:
	./spiralPDF
longtest:
	./spiralPDF "Gentoo is a free operating system based on either Linux or FreeBSD that can be automatically optimized and customized for just about any application or need."