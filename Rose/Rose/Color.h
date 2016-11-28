#pragma once

class Color;
class ColorRGB;
class ColorHSV;

class Color 
{
public:
	float x, y, z;

	Color();
	Color(float x, float y, float z);

	friend Color operator+(const Color& c, const Color& c2);
	friend Color operator%(const Color& c, const Color& c2);

	operator ColorRGB();
	operator ColorHSV();

	~Color() {};

};



class ColorRGB
{
public:

	float r, g, b, a;

	ColorRGB();
	ColorRGB(float r, float g, float b);
	ColorRGB(int data);

	friend ColorRGB operator+(const ColorRGB& c, const ColorRGB& c2);
	friend ColorRGB operator%(const ColorRGB& c, const ColorRGB& c2);

	operator Color();
	operator ColorHSV();

	~ColorRGB() {};
};

class ColorHSV {
public:
	float h, s, v;

	ColorHSV();
	ColorHSV(float h, float s, float v);

	friend ColorHSV operator%(const ColorHSV& c, const float hp);
	operator ColorRGB();
	operator Color();

};

