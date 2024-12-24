#pragma once
class Vector2 {
	int x, y;
public :
    double lengthpts(int x1, int y1, int x2, int y2) {
        return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
    }
    bool inCircle(int x, int y, int mx, int my) {
        if (lengthpts(x, y, mx, my) <= Bsize) return true;
        return false;
    }
};
