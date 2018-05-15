// A2: Classes and Facades
// Nick(Mykola) Pershyn
// CS3505 (CS5020)#include <string>#include <iostream>

#include <cmath>
#include "Spiral.h"


Spiral::Spiral(double centerX, double centerY, double angle, double radius = 20.0)
{
	m_centerX = centerX;
	m_centerY = centerY;
	m_angle = (-angle + 90) * M_PI / 180;
	m_radius = std::abs(radius);
	if (m_radius < 20.0)
		m_radius = 20.0;
	return;
}

Spiral::~Spiral()
{
	return;
}

double Spiral::get_text_x() const
{
	return m_centerX + cos(m_angle) * m_radius;
}

double Spiral::get_text_y() const
{
	return m_centerY + sin(m_angle) * m_radius;
}


double Spiral::get_spiral_angle() const
{
	return m_angle * 180 / M_PI;
}


double Spiral::get_text_angle() const
{
	return m_angle * 180 / M_PI - 90;
}

Spiral& Spiral::operator++()
{
	const double dl = 17;
	const double da = dl / m_radius;
	m_angle -= da;
	m_radius += da / M_PI * 20;
	return *this;
}

Spiral Spiral::operator++(int)
{
	Spiral tmp(*this);
	operator++();
	return tmp;
}

std::ostream& operator<<(std::ostream& os, const Spiral& obj)
{
    os << "Spiral: m_center(" << obj.m_centerX << ", " << obj.m_centerY << "), m_angle(" << obj.m_angle << "), m_radius(" << obj.m_radius << ")";
    return os;
}
