class XYPoint{
    public:
    sq(double x, double y){
        return x*x + y*y;
    }
}

class XYZPoint : public XYPoint{
    public:
    double sq(double x, double y, double z){
        return XYPoint.sq(x,y) + z*z;
    }
}