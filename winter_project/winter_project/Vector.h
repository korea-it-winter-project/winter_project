#pragma once
#include <cmath>

struct Vector {
public:
    // 생성자
    Vector(float _x = 0.f, float _y = 0.f) : x(_x), y(_y) {}

    // 연산자 오버로딩 (결과를 반환하는 연산)
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // 복합 할당 연산자
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

    // 벡터의 길이 계산
    float LengthSquared() const {
        return x * x + y * y;
    }

    float Length() const {
        return std::sqrt(LengthSquared());
    }

    // 정규화
    void Normalize() {
        float len = Length();
        if (len < 1e-6f) return; // 아주 작은 값은 무시
        x /= len;
        y /= len;
    }

    // 멤버 변수
    float x = 0.0f;
    float y = 0.0f;
};

// FPOINT 타입 정의 (Vector로 대체 가능)
using FPOINT = Vector;
