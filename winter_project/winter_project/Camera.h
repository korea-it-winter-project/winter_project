#pragma once
#pragma once
#include "Vector.h"

class Camera {
private:
    Vector position;      // ī�޶� ��ġ
    Vector viewportSize;  // ����Ʈ ũ��

public:
    Camera() {};
    Camera(float width, float height) { 
        viewportSize.x = width;
        viewportSize.y = height;
        position = Vector(0, 0);
    };

    void Move(const Vector& _position) {
        position += _position; // ī�޶� �̵�
    }

    void SetViewportSize(float width, float height) {
        viewportSize.x = width;
        viewportSize.y = height;
    }

    Vector GetPosition() const { return position; }

    // ���� ��ǥ �� ȭ�� ��ǥ ��ȯ
    Vector WorldToScreen(const Vector& worldPos) const {
        return Vector(
            worldPos.x - position.x + viewportSize.x / 2.0f,
            worldPos.y - position.y + viewportSize.y / 2.0f
        );
    }
};
