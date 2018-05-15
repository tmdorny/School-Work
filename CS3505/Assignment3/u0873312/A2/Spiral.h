// A2: Classes and Facades
// Nick(Mykola) Pershyn
// CS3505 (CS5020)
#pragma once
#include <iostream>

class Spiral
{
	double m_centerX;
	double m_centerY;
	double m_angle;
	double m_radius;
public:
	//angle in degrees which gives the starting angle clockwise from vertical for the text to begin drawing
	Spiral(double centerX, double centerY, double angle, double initial_radius);
	~Spiral();
	
	double get_text_x() const;
	double get_text_y() const;
	double get_spiral_angle() const;
	double get_text_angle() const;

	Spiral& operator++();
	Spiral  operator++(int);
	
	friend std::ostream& operator<<(std::ostream& os, const Spiral& obj);
	//An overloaded ostream << function which reports in a nicely formatted way the state of a Spiral object. Rely on users of this function to provide any desired newlines after outputting the spiral object.
};