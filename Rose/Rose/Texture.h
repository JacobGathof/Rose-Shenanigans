#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include <fstream>
#include <string>

class Texture
{
public:
	GLuint tbo;
	GLenum textureType;
	GLenum format;

	void bind();
	Texture(char* filename);
	Texture(GLuint tbo) : tbo(tbo) {}
	Texture() {};
	~Texture();
};
