#pragma once
#include <math.h>

struct Vector {
public:
	Vector() {};
	Vector(float _x, float _y) :x(_x), y(_y) {};
	Vector operator+(const Vector& other) {
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
	};
	Vector operator-(const Vector& other) {
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
	};
	Vector operator*(const Vector& other) {
		Vector ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
	};
	void operator+=(const Vector& other) {
		x += other.x;
		y += other.y;
	};
	void operator-=(const Vector& other) {
		x -= other.x;
		y -= other.y;
	};

	void operator*=(const Vector& other) {
		x *= other.x;
		y *= other.y;
	};
	float LengthSquared() {
		return x * x + y * y;
	}
	float Length() {
		return sqrt(LengthSquared());
	}
	void Normalize() {
		float len = Length();
		if (len < 000000.1f)return;
		x /= len;
		y /= len;
	}


	float x=0;
	float y = 0;
};

using FPOINT = Vector;