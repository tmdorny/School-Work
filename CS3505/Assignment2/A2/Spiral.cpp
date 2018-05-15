/*  Assignment 2 Spiral Class. Written by Tim Dorny u0829896.
 This class provides functionality for spiral computations.*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Spiral.h"

double const startRadius = 5;
double const startAngle = 45;
double angleGrowth = 10;
double radiusGrowth = 2;
    Spiral::Spiral(double centerX, double centerY){

        // Initaillize spiral values.
        xPos = centerX;
        yPos = centerY;
        sAngle = startAngle;
        radius = startRadius;
        tAngle = 45;
    }
    void Spiral::operator ++ (){
        Increment();
    }
    void Spiral::operator ++ (int){
        Increment();
    }
    double Spiral::get_text_x(){
        return xPos;
    }
    double Spiral::get_text_y(){
        return yPos;
    }
    double Spiral::get_spiral_angle(){
        return sAngle;
    }
    double Spiral::get_text_angle(){
        return tAngle;
    }

std::ostream& operator<<(std::ostream& os, const Spiral s){
        os << "Position (" << s.xPos << "," << s.yPos << "). Spiral angle: " << s.sAngle << ". Text angle: " << s.tAngle << ".";
        return os;
    }

// Method that is called when spiral "increments".
    void Spiral::Increment(){
        // Increment angle and radius
        sAngle += angleGrowth;
        radius += radiusGrowth;
        // Reduce angle growth as radius gets bigger.(ratio may need adjustment)
        angleGrowth -= radiusGrowth / 10;
        // Text angle is perpendicular to current angle of spiral.
        tAngle = sAngle - 90;
        // Set x and y positions based on angle and radius.
        xPos = cos(sAngle) * radius;
        yPos = sin(sAngle) * radius;
    }
