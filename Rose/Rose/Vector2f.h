#pragma once
#include <string>
class Vector2f
{
public:

	float x, y;

	float magnitude();
	Vector2f normalize();

	friend Vector2f operator*(float f, const Vector2f &v);
	friend Vector2f operator*(const Vector2f &v, float f);
	friend Vector2f operator/(float f, const Vector2f &v);
	friend Vector2f operator/(const Vector2f &v, float f);
	friend Vector2f operator+(const Vector2f &v, const Vector2f &v2);
	friend Vector2f operator-(const Vector2f &v, const Vector2f &v2);
	Vector2f& operator+=(const Vector2f &v);
	Vector2f& operator-=(const Vector2f &v);
	Vector2f& operator*=(const float f);
	Vector2f& operator/=(const float f);

	static float distance(const Vector2f &v, const Vector2f &v2) {
		return Vector2f(v.x - v2.x, v.y - v2.y).magnitude();
	}

	std::string toString() {
		return std::to_string(x) + "," + std::to_string(y);
	}


	Vector2f();
	Vector2f(float x, float y);
};

