#pragma once
#pragma once
#include "Vector.h"
class Camera {
private:
    Vector position; // 카메라 위치
    float viewportWidth;
    float viewportHeight;

public:
    Camera() {};
    Camera(float width, float height) : position(0.0f, 0.0f), viewportWidth(width), viewportHeight(height) {}

    void Move(const Vector& offset) { position += offset; }

    Vector WorldToScreen(const Vector& worldPos) {
        return Vector(worldPos.x - position.x, worldPos.y - position.y);
    }

    bool IsInView(const Vector& worldPos, float objectWidth, float objectHeight) {
        Vector screenPos = WorldToScreen(worldPos);
        return (screenPos.x + objectWidth >= 0 && screenPos.x <= viewportWidth &&
            screenPos.y + objectHeight >= 0 && screenPos.y <= viewportHeight);
    }

    void SetViewportSize(float width, float height) {
        viewportWidth = width;
        viewportHeight = height;
    }
};

