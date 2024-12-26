#pragma once
class Vector2 {

public :
    double x, y;

    Vector2 zero() { return Vector2{ 0,0 }; }
    Vector2 up() { return Vector2{ 0,1 }; }
    Vector2 right() { return Vector2{ 1,0 }; }
    Vector2 down() { return Vector2{ 0,-1 }; }
    Vector2 lift() { return Vector2{ -1,0 }; }
};
