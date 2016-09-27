#include "Vector2f.h"
#include <iostream>


float Vector2f::magnitude()
{
	return sqrt(x*x + y*y);
}

Vector2f Vector2f::normalize()
{
	if (x == 0 && y == 0) return Vector2f(0, 0);
	float mag = magnitude();
	return Vector2f(x/mag, y/mag);
}



/*------------------------

		Overloads

-------------------------*/

Vector2f & Vector2f::operator+=(const Vector2f & v){	
	x += v.x;
	y += v.y;
	return *this;
}
Vector2f & Vector2f::operator-=(const Vector2f & v) {
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2f & Vector2f::operator*=(const float f) {
	x *= f;
	y *= f;
	return *this;
}
Vector2f & Vector2f::operator/=(const float f) {
	x /= f;
	y /= f;
	return *this;
}

std::string Vector2f::toIntString(){
	return std::to_string((int)x) + "," + std::to_string((int)y);
}

std::ostream &operator<<(std::ostream& os, const Vector2f &v){
	os << "[" << v.x << "," << v.y << "]";
	return os;
}

Vector2f operator*(float f, const Vector2f &v) {
	return Vector2f(v.x * f, v.y * f);
}
Vector2f operator*(const Vector2f &v, float f) {
	return Vector2f(v.x * f, v.y * f);
}
Vector2f operator/(float f, const Vector2f &v) {
	return Vector2f(v.x / f, v.y / f);
}
Vector2f operator/(const Vector2f &v, float f) {
	return Vector2f(v.x / f, v.y / f);
}
Vector2f operator+(const Vector2f &v, const Vector2f &v2) {
	return Vector2f(v.x + v2.x, v.y + v2.y);
}
Vector2f operator-(const Vector2f &v, const Vector2f &v2) {
	return Vector2f(v.x - v2.x, v.y - v2.y);
}

//Distance operator
float operator^(const Vector2f &v, const Vector2f &v2) {
	return Vector2f(v.x - v2.x, v.y - v2.y).magnitude();
}

//Magnitude operator
float operator~(const Vector2f &v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

Vector2f::Vector2f(){
	x = 0;
	y = 0;
}

Vector2f::Vector2f(float x, float y){
	this->x = x;
	this->y = y;
}
