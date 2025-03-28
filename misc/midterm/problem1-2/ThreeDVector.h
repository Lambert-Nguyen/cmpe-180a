#ifndef THREEDVECTOR_H
#define THREEDVECTOR_H

#include "TwoDVector.h"
#include <iostream>
#include <cmath>

class ThreeDVector : public TwoDVector {
private:
    double z;
public:
    // Constructors
    ThreeDVector();                                      // Default constructor
    ThreeDVector(const ThreeDVector &vec);               // Copy constructor
    ThreeDVector(double xVal, double yVal, double zVal);   // Parameterized constructor

    // Getter and Setter for the z component
    double getZ() const;
    void setZ(double zVal);

    // Returns the angle (in radians) of the projection onto the x-y plane.
    double getTheta() const;

    // Overloaded operator *: Dot product (including the z component)
    double operator*(const ThreeDVector &vec) const;

    // Overloaded operator +: Component-wise addition.
    ThreeDVector operator+(const ThreeDVector &vec) const;

    // Overloaded operator -: Component-wise subtraction.
    ThreeDVector operator-(const ThreeDVector &vec) const;

    // Overloaded operator /: Divide each component by a scalar.
    ThreeDVector operator/(double scalar) const;

    // Overloaded prefix ++: Increase all components (x, y, and z) by 1.
    ThreeDVector& operator++();

    // Overloaded prefix --: Decrease all components (x, y, and z) by 1.
    ThreeDVector& operator--();

    // Overloaded function call operator to return the magnitude of the vector.
    double operator()() const;

    // Overloaded << operator for pretty printing the vector components.
    friend std::ostream& operator<<(std::ostream &os, const ThreeDVector &vec);
};

#endif // THREEDVECTOR_H
