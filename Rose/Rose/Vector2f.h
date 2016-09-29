#pragma once
#include <string>
#include <iostream>
class Vector2f
{
public:

	float x, y;

	float magnitude();
	Vector2f normalize();
	Vector2f round();

	friend Vector2f operator*(float f, const Vector2f &v);
	friend Vector2f operator*(const Vector2f &v, float f);
	friend Vector2f operator/(float f, const Vector2f &v);
	friend Vector2f operator/(const Vector2f &v, float f);
	friend Vector2f operator+(const Vector2f &v, const Vector2f &v2);
	friend Vector2f operator-(const Vector2f &v, const Vector2f &v2);
	friend float operator^(const Vector2f &v, const Vector2f &v2);
	friend std::ostream &operator<<(std::ostream& os, const Vector2f &v);
	friend float operator~(const Vector2f &v);
	friend Vector2f operator%(const Vector2f& v, const Vector2f& v2);
	friend bool operator==(const Vector2f& v, const Vector2f& v2);
	friend bool operator<(const Vector2f& v, const Vector2f& v2);

	Vector2f& operator+=(const Vector2f &v);
	Vector2f& operator-=(const Vector2f &v);
	Vector2f& operator*=(const float f);
	Vector2f& operator/=(const float f);

	std::string toIntString();

	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f &v);
};

