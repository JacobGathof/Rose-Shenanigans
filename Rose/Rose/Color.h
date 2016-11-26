#pragma once
class Color
{
public:

	float r, g, b, a;
	

	Color();
	Color(float r, float g, float b);
	Color(int data);

	friend Color operator+(const Color& c, const Color& c2);
	friend Color operator%(const Color& c, const Color& c2);

	~Color() {};
};

class ColorHSV {
public:
	float h, s, v;

	ColorHSV(float h, float s, float v);

	friend ColorHSV operator%(const ColorHSV& c, const float hp);
	operator Color();

};

