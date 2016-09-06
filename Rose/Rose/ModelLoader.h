#pragma once
#include "Model.h"
#include "GL\glew.h"

class ModelLoader
{
public:

	static Model* loadModel(float* vertices, int length);
	static Model* loadModel(float* vertices, float* texCoords, int length);

	ModelLoader();
	~ModelLoader();

private:

	/*Attrib location in the Shaders, number of components per Vec, Pointer to data, size of data in bytes*/
	static void loadBuffer(int attribLocation, int size, float* data, int length);

};

