#include "ThreeDVector.h"

// Default constructor: initializes base (TwoDVector) and sets z to 0.
ThreeDVector::ThreeDVector() : TwoDVector(), z(0) { }

// Copy constructor: uses base class copy constructor and copies z.
ThreeDVector::ThreeDVector(const ThreeDVector &vec) : TwoDVector(vec.getX(), vec.getY()), z(vec.z) { }

// Parameterized constructor: initializes base class with x and y, and sets z.
ThreeDVector::ThreeDVector(double xVal, double yVal, double zVal)
    : TwoDVector(xVal, yVal), z(zVal) { }

// Getter for the z component.
double ThreeDVector::getZ() const {
    return z;
}

// Setter for the z component.
void ThreeDVector::setZ(double zVal) {
    z = zVal;
}

// getTheta() returns the angle (in radians) of the projection of the vector onto the x-y plane.
double ThreeDVector::getTheta() const {
    return std::atan2(getY(), getX());
}

// Overloaded operator * for the dot product, including the z component.
double ThreeDVector::operator*(const ThreeDVector &vec) const {
    return getX() * vec.getX() + getY() * vec.getY() + z * vec.z;
}

// Overloaded operator + for component-wise addition.
ThreeDVector ThreeDVector::operator+(const ThreeDVector &vec) const {
    return ThreeDVector(getX() + vec.getX(), getY() + vec.getY(), z + vec.z);
}

// Overloaded operator - for component-wise subtraction.
ThreeDVector ThreeDVector::operator-(const ThreeDVector &vec) const {
    return ThreeDVector(getX() - vec.getX(), getY() - vec.getY(), z - vec.z);
}

// Overloaded operator / to divide each component by a scalar.
ThreeDVector ThreeDVector::operator/(double scalar) const {
    return ThreeDVector(getX() / scalar, getY() / scalar, z / scalar);
}

// Overloaded prefix ++: Increases x, y, and z components by 1.
ThreeDVector& ThreeDVector::operator++() {
    setX(getX() + 1);
    setY(getY() + 1);
    z += 1;
    return *this;
}

// Overloaded prefix --: Decreases x, y, and z components by 1.
ThreeDVector& ThreeDVector::operator--() {
    setX(getX() - 1);
    setY(getY() - 1);
    z -= 1;
    return *this;
}

// Overloaded function call operator to return the magnitude of the 3D vector.
double ThreeDVector::operator()() const {
    return std::sqrt(getX()*getX() + getY()*getY() + z*z);
}

// Overloaded << operator for pretty printing all three vector components.
std::ostream& operator<<(std::ostream &os, const ThreeDVector &vec) {
    os << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.z << ")";
    return os;
}
