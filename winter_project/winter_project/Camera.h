#pragma once
#pragma once
#include "Vector.h"

class Camera {
private:
    Vector position;      // 카메라 위치
    Vector viewportSize;  // 뷰포트 크기

public:
    Camera() {};
    Camera(float width, float height) { 
        viewportSize.x = width;
        viewportSize.y = height;
        position = Vector(0, 0);
    };

    void Move(const Vector& _position) {
        position += _position; // 카메라 이동
    }

    void SetViewportSize(float width, float height) {
        viewportSize.x = width;
        viewportSize.y = height;
    }

    Vector GetPosition() const { return position; }

    // 월드 좌표 → 화면 좌표 변환
    Vector WorldToScreen(const Vector& worldPos) const {
        return Vector(
            worldPos.x - position.x + viewportSize.x / 2.0f,
            worldPos.y - position.y + viewportSize.y / 2.0f
        );
    }
};
