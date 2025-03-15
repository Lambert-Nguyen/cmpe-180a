#include "cylinder.h"

Cylinder::Cylinder():Circle(), height(1.0) {}
Cylinder::Cylinder(double r, double h): Circle(r),height(h) {}
Cylinder::Cylinder(const Cylinder &other) : Circle(other), height(other.height){}

Cylinder::~Cylinder(){}

double Cylinder::calVolume() const {
    return M_PI * getRadius() * getRadius() * height;
}

double Cylinder::calSurfaceArea()const {
    return 2 * M_PI * getRadius() * (getRadius()+height);
}

void Cylinder::setHeight(double h){
    height = h;
}
double Cylinder::getHeight() const {
    return height;
}