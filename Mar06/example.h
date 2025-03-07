#include <iostream>
using std::iostream;
class XYPoint{
    public:
    double operator*(const XYPoint &o);
    bool operator!();
    friend iostream& operator<<(iostream &o, const XYPoint &p);
}