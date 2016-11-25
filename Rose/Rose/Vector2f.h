#pragma once
#include <string>
#include <iostream>
#define ZERO_VECTOR Vector2f(0,0)


/*
	Vector2f class
		Used to describe a size, direction, or position.
		Contains an X and Y as floating point values.
		Most operator overloads are implemented, as well as functions to round and normalize

*/
class Vector2f
{
public:
	
	float x, y;

	/*Return the magnitude of the Vector interpreted as a direction*/
	float magnitude();

	/*Return a Vector in the same direction as the original which has a magnitude of 1*/
	Vector2f normalize();

	/*Round each component (X, Y) to the nearest int (floor)*/
	Vector2f round();

	/*Scale a Vector2f by a float*/
	friend Vector2f operator*(float f, const Vector2f &v);

	/*Scale a Vector2f by a float*/
	friend Vector2f operator*(const Vector2f &v, float f);

	/*Scale a Vector2f by a float*/
	friend Vector2f operator/(float f, const Vector2f &v);

	/*Scale a Vector2f by a float*/
	friend Vector2f operator/(const Vector2f &v, float f);

	/*Add two Vectors together with component-wise addition*/
	friend Vector2f operator+(const Vector2f &v, const Vector2f &v2);

	/*Subtract two Vectors with component-wise subtraction*/
	friend Vector2f operator-(const Vector2f &v, const Vector2f &v2);

	/*Shorthand operator -> return the distance between two Vectors*/
	friend float operator^(const Vector2f &v, const Vector2f &v2);

	/*Used for printing Vectors to cout*/
	friend std::ostream &operator<<(std::ostream& os, const Vector2f &v);

	/*Shorthand operator -> return the magnitude of a Vector*/
	friend float operator~(const Vector2f &v);

	/*Random distribution operator -> increase 1st by a random fraction of the 2nd*/
	friend Vector2f operator%(const Vector2f& v, const Vector2f& v2);

	/*Equals operator -> Two Vectors are equal if their rounded values are equal*/
	friend bool operator==(const Vector2f& v, const Vector2f& v2);

	/*Comparison operator -> compare two Vectors based on their Y components*/
	friend bool operator<(const Vector2f& v, const Vector2f& v2);


	/*+= overload*/
	Vector2f& operator+=(const Vector2f &v);

	/*-= overload*/
	Vector2f& operator-=(const Vector2f &v);

	/**= overload*/
	Vector2f& operator*=(const float f);

	/*/= overload*/
	Vector2f& operator/=(const float f);

	/*
	Convert a Vector to a string.
	Used for saving positions
	*/
	std::string toIntString();

	/*Default Constructor. X = 0, Y = 0*/
	Vector2f();

	/*Constructor. X = x, Y = x*/
	Vector2f(float x, float y);

	/*Copy Constructor. X = v.x, Y = v.y*/
	Vector2f(const Vector2f &v);
};

