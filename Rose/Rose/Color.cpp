#include "Color.h"
#include <iostream>

/************Color*************/
Color::Color() {
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
};

Color::Color(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Color::operator ColorRGB(){
	return ColorRGB(x, y, z);
}

Color::operator ColorHSV(){
	return ColorHSV(x, y, z);
}

Color operator+(const Color& c, const Color& c2) {
	return Color(c.x + c2.x, c.y + c2.y, c.z + c2.z);
}

Color operator%(const Color& c, const Color& c2) {

	float random_r = ((float)rand() / RAND_MAX);
	float random_g = ((float)rand() / RAND_MAX);
	float random_b = ((float)rand() / RAND_MAX);

	return Color(c.x + random_r*c2.x, c.y + random_g*c2.y, c.z + random_b*c2.z);
}




/************ColorRGB*************/
ColorRGB::ColorRGB() {
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
};

ColorRGB::ColorRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

ColorRGB::ColorRGB(int data) {
	r = ((data & 0xFF000000) / 255.0f);
	g = ((data & 0x00FF0000) / 255.0f);
	b = ((data & 0x0000FF00) / 255.0f);
	a = ((data & 0x000000FF) / 255.0f);
}

ColorRGB::operator Color(){
	return Color(r, g, b);
}

ColorRGB operator+(const ColorRGB& c, const ColorRGB& c2) {
	return ColorRGB(c.r + c2.r, c.g + c2.g, c.b + c2.b);
}

ColorRGB operator%(const ColorRGB& c, const ColorRGB& c2) {

	float random_r = ((float)rand() / RAND_MAX);
	float random_g = ((float)rand() / RAND_MAX);
	float random_b = ((float)rand() / RAND_MAX);

	return ColorRGB(c.r + random_r*c2.r, c.g + random_g*c2.g, c.b + random_b*c2.b);
}



/************ColorHSV*************/
ColorHSV::ColorHSV(){
	this->h = 1.0f;
	this->s = 1.0f;
	this->v = 1.0f;
}

ColorHSV::ColorHSV(float h, float s, float v) {

	this->h = h;
	this->s = s;
	this->v = v;

}

ColorHSV::operator ColorRGB()
{

	float c = v*s;
	float hp = h / 60;
	int hpi = (int)hp;
	float m = v - c;
	float r1, g1, b1;
	float x = c * (1 - abs(fmod(hp, 2) - 1));

	switch (hpi) {
	case 0: r1 = c; g1 = x; b1 = 0; break;
	case 1: r1 = x; g1 = c; b1 = 0; break;
	case 2: r1 = 0; g1 = c; b1 = x; break;
	case 3: r1 = 0; g1 = x; b1 = c; break;
	case 4: r1 = x; g1 = 0; b1 = c; break;
	case 5: r1 = c; g1 = 0; b1 = x; break;
	}

	return ColorRGB(r1+m, g1+m, b1+m);
}

ColorHSV::operator Color(){

	return Color(h, s, v);
}

ColorHSV operator%(const ColorHSV& c, const float hp) {

	float new_h = ((float)rand() / RAND_MAX)*hp + c.h;
	new_h = (new_h >= 360) ? new_h - 360 : new_h;

	return ColorHSV(new_h, c.s, c.v);
}