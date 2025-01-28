#pragma once
#include <cmath>

struct Vector {
public:
    // ������
    Vector(float _x = 0.f, float _y = 0.f) : x(_x), y(_y) {}

    // ������ �����ε� (����� ��ȯ�ϴ� ����)
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // ���� �Ҵ� ������
    void operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    // ������ ���� ���
    float LengthSquared() const {
        return x * x + y * y;
    }

    float Length() const {
        return std::sqrt(LengthSquared());
    }

    // ����ȭ
    void Normalize() {
        float len = Length();
        if (len < 1e-6f) return; // ���� ���� ���� ����
        x /= len;
        y /= len;
    }

    // ��� ����
    float x = 0.0f;
    float y = 0.0f;
};

// FPOINT Ÿ�� ���� (Vector�� ��ü ����)
using FPOINT = Vector;
