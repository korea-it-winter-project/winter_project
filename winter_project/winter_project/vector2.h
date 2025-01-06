#pragma once
#include "init.h"
#include <math.h>

class Vector2 {

public :
    double x, y;
};
Vector2 zero() { return Vector2{ 0,0 }; }

double lengthpts(int x1, int y1, int x2, int y2) {
    return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}
