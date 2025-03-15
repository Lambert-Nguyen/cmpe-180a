#ifndef CYLINDER_H
#define CYLINDER_H

#include "circle.h" //assumming cirle class is fully implemented

class Cylinder : public Circle{
    private:
    double height;
    public:
    Cylinder();
    Cylinder(double radius, double height);
    Cylinder(const Cylinder &other);
    
    ~Cylinder();

    double calVolume() const;
    double calSurfaceArea() const;

    void setHeight(double h);
    double getHeight() const;
};


#endif