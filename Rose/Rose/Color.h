#pragma once
class Color
{
public:

	float r, g, b, a;

	Color() {
		r = 0.5f;
		g = 0.5f;
		b = 0.5f;
		a = 1.0f;
	};
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1.0f;
	};
	Color(int data) {
		r = ((data & 0xFF000000) / 255.0f);
		g = ((data & 0x00FF0000) / 255.0f);
		b = ((data & 0x0000FF00) / 255.0f);
		a = ((data & 0x000000FF) / 255.0f);
	}
	~Color();
};

