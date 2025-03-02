// Define and implement a c++ class named XYPoint that has two data members named x and y of type double to store the coordinates of a point in two dimensions:
// define a default constructor that sets x and y to zero and define another constructor that takes x and y as arguments in that order. 
// Define all getters and setters: setX, setY, getX, getY. 
// Include only two files with the class implementation not main function, our test will add main. You must submit XYPoint.cc and XYPoint.h only.
#include "XYPoint.h"

    XYPoint::XYPoint() : x(0), y(0) {}
    XYPoint::XYPoint(double xx, double yy) : x(xx), y(yy) {}

    void XYPoint::setX(double xx){
        x = xx;
    }
    void XYPoint::setY(double yy){
        y = yy;
    }
    double XYPoint::getX() const{
        return x;
    }
    double XYPoint::getY() const{
        return y;
    }

