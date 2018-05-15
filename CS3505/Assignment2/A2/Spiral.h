#ifndef SPIRAL_IS_FUN
#define SPIRAL_IS_FUN

#include <iostream>

class Spiral {
public:
    double xPos;
    double yPos;
    double sAngle;
    double tAngle;
    double radius;
    Spiral(double centerX, double centerY);
    void operator ++ ();
    void operator ++ (int);
    double get_text_x();
    double get_text_y();
    double get_spiral_angle();
    double get_text_angle();
    void Increment();
};
std::ostream& operator<< (std::ostream& os, const Spiral&);
#endif