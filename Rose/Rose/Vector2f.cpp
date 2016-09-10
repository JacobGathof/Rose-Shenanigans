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

Vector2f::Vector2f()
{
	x = 0;
	y = 0;
}

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2f::~Vector2f()
{
}
