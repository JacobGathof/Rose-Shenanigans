#include "Vector2f.h"
#include <iostream>


float Vector2f::magnitude(){
	return sqrt(x*x + y*y);
}

Vector2f Vector2f::normalize(){
	if (x == 0 && y == 0) return Vector2f(0, 0);
	float mag = magnitude();
	return Vector2f(x/mag, y/mag);
}

Vector2f Vector2f::round(){
	int xx = (x < 0) ? (int)(x - 1) : (int)x;
	int yy = (y < 0) ? (int)(y - 1) : (int)y;
	return Vector2f(xx,yy);
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

//Random deviation operator
Vector2f operator%(const Vector2f& v, const Vector2f& v2) {

	float random_x = ((float)rand() / RAND_MAX);
	float random_y = ((float)rand() / RAND_MAX);

	return Vector2f(v.x + random_x*v2.x, v.y + random_y*v2.y);
}

Vector2f operator%=(const Vector2f& v, const Vector2f& v2) {

	float random_x = 2*((float)rand() / RAND_MAX)-1;
	float random_y = 2*((float)rand() / RAND_MAX)-1;

	return Vector2f(v.x + random_x*v2.x, v.y + random_y*v2.y);
}

bool operator==(const Vector2f& v, const Vector2f& v2) {
	return (int)v.x == (int)v2.x && (int)v.y == (int)v2.y;
}

bool operator<(const Vector2f& v, const Vector2f& v2) {
	if ((int)v.x == (int)v2.x) return (int)v.y < (int)v2.y;
	return (int)v.x < (int)v2.x;
}

Vector2f::Vector2f(){
	x = 0;
	y = 0;
}

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(const Vector2f & v){
	this->x = v.x;
	this->y = v.y;
}


