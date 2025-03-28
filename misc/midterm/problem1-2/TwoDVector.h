#ifndef TWODVECTOR_H
#define TWODVECTOR_H

#include <iostream>
#include <cmath>

class TwoDVector {
private:
    double x;
    double y;
public:
    // Constructors
    TwoDVector();                          // Default constructor
    TwoDVector(const TwoDVector &vec);     // Copy constructor
    TwoDVector(double xVal, double yVal);  // Parameterized constructor

    // Getters
    double getX() const;
    double getY() const;

    // Setters
    void setX(double xVal);
    void setY(double yVal);

    // Returns the angle (in radians) of the vector with respect to the positive x-axis.
    double getTheta() const;

    // Overloaded operator ! to reverse the direction of the vector.
    TwoDVector operator!() const;

    // Overloaded operator * to perform the dot product of two vectors.
    double operator*(const TwoDVector &vec) const;

    // Overloaded operator + to add the components of two vectors.
    TwoDVector operator+(const TwoDVector &vec) const;

    // Overloaded operator - to subtract the components of two vectors.
    TwoDVector operator-(const TwoDVector &vec) const;

    // Overloaded operator / to divide a vector by a scalar.
    TwoDVector operator/(double scalar) const;

    // Overloaded prefix ++ operator to increase both x and y components by 1.
    TwoDVector& operator++(); // Prefix increment

    // Overloaded prefix -- operator to decrease both x and y components by 1.
    TwoDVector& operator--(); // Prefix decrement

    // Overloaded function call operator to return the magnitude of the vector.
    double operator()() const;

    // Overloaded << operator for pretty printing the vector components.
    friend std::ostream& operator<<(std::ostream &os, const TwoDVector &vec);
};

#endif // TWODVECTOR_H
