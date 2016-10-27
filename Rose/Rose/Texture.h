#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include <fstream>
#include <string>
#include <iostream>

class Texture
{
public:
	GLuint tbo;
	GLenum textureType;
	GLenum format;

	int numberOfRows=1;
	int numberOfColumns=1;

	void bind();
	void init(char * filename);

	Texture(char* filename);
	Texture(char* filename, int numRows, int numCol);
	Texture(GLuint tbo) : tbo(tbo) {
		textureType = GL_TEXTURE_2D;
	}
	Texture() {};
	~Texture();
};