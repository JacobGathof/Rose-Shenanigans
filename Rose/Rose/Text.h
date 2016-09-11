#pragma once
#include "GL\glew.h"
#include "Vector2f.h"
#include <string>


class Text
{
public:

	GLuint VAO;
	GLuint pos_buffer, tex_buffer;
	Vector2f position;
	Vector2f scale;
	std::string data;
	int length;
	int charsToRender;

	Text(Vector2f position, std::string data, Vector2f scale);
	Text() {};

	~Text() {};

	void writeCharacterData(std::string string, float *pos, float *tex);
	void updateVAO(float * pos, int pos_size, float * tex, int tex_size);
	void setText(std::string str);
	int getNumberOfVertices();
	void addCharactersToRender() { if (charsToRender < length * 6) charsToRender += 6; }
	void reset() { charsToRender = 0; }
	void draw();
};
