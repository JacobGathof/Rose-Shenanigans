#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Vector2f.h"
#include <vector>
#include <string>



class Character
{
public:

	char ID;
	int x, y, width, height, xoffset, yoffset, xadvance;

	Character(std::vector<int> data);
	Character() {};
	~Character() {};
};

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
	void generateVAO();
	void setText(std::string str);
	int getNumberOfVertices();
	bool addCharactersToRender(int n = 1);
	void reset() { charsToRender = 0; }
	void draw();
};



