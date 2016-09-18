#pragma once
#include <string>
class Vector2f
{
public:

	float x, y;

	float magnitude();
	Vector2f normalize();

	friend Vector2f operator*(float f, const Vector2f &v) {
		return Vector2f(v.x * f, v.y * f);
	}
	friend Vector2f operator*(const Vector2f &v, float f) {
		return Vector2f(v.x * f, v.y * f);
	}

	friend Vector2f operator+(const Vector2f &v, const Vector2f &v2) {
		return Vector2f(v.x +v2.x, v.y +v2.y);
	}

	friend Vector2f operator-(const Vector2f &v, const Vector2f &v2) {
		return Vector2f(v.x - v2.x, v.y - v2.y);
	}

	static float distance(const Vector2f &v, const Vector2f &v2) {
		return Vector2f(v.x - v2.x, v.y - v2.y).magnitude();
	}

	Vector2f& operator+=(const Vector2f &v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	std::string toString() {
		return std::to_string((int)x) + "," + std::to_string((int)y);
	}


	Vector2f();
	Vector2f(float x, float y);
	~Vector2f();
};

