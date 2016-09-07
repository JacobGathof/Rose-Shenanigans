#pragma once
#include "GL\glew.h"


class Model
{
public:

	GLuint VAO;
	int numberOfVertices;

	/*Construct a Model Object with a VAO and the Number of Vertices to render*/
	Model(int vao, int num);
	Model();
	~Model();
};

