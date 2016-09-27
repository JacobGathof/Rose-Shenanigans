#include "Color.h"
#include <iostream>

Color::Color() {
	r = 0.5f;
	g = 0.5f;
	b = 0.5f;
	a = 1.0f;
};

Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
};

Color::Color(int data) {
	r = ((data & 0xFF000000) / 255.0f);
	g = ((data & 0x00FF0000) / 255.0f);
	b = ((data & 0x0000FF00) / 255.0f);
	a = ((data & 0x000000FF) / 255.0f);
}

Color operator+(const Color& c, const Color& c2) {
	return Color(c.r + c2.r, c.g + c2.g, c.b + c2.b);
}

Color operator%(const Color& c, const Color& c2) {

	float random_r = ((float)rand() / RAND_MAX);
	float random_g = ((float)rand() / RAND_MAX);
	float random_b = ((float)rand() / RAND_MAX);

	return Color(c.r + random_r*c2.r, c.g + random_g*c2.g, c.b + random_b*c2.b);
}