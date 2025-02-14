#include <math.h>

#include "sqr.h"
#include "distance.h"

int float distance(struct XYPoint xy) {
    return sqrt(sqr(xy.x) + sqr(xy.y));
}