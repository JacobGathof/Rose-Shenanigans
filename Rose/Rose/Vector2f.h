#pragma once
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


	Vector2f();
	Vector2f(float x, float y);
	~Vector2f();
};

