#include "example.h"

    double XYPoint::operator*(const XYPoint &o) const{
        return (o.x * x + o.y * y);
    }
    bool XYPoint::operator!()const{
        return(!x&&!y);
    }
    iostream& operator<<(iostream &o, const XYPoint &p){
        o<<"x="<<p.x<<endl;
        o<<"y="<<p.y<<endl;
        return o;
    }
