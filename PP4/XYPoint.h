#ifndef XYPOINT_H
#define XYPOINT_H

class XYPoint{
    private:
    double x;
    double y;
    public:
    XYPoint();
    XYPoint(double xx, double yy);
    void setX(double xx);
    void setY(double yy);
    double getX() const;
    double getY() const;
};

#endif