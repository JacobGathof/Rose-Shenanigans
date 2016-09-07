#include "ModelLoader.h"



Model * ModelLoader::loadModel(float * vertices, int length){

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	loadBuffer(0, 2, vertices, length);

	Model * m = new Model(VAO, length);
	return m;
}

Model * ModelLoader::loadModel(float * vertices, float * texCoords, int length)
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	loadBuffer(0, 2, vertices, length);
	loadBuffer(1, 2, texCoords, length);

	Model * m = new Model(VAO, length/2);
	return m;
}

ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

void ModelLoader::loadBuffer(int attribLocation, int size, float * data, int length){
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, length*4, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribLocation, size, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(attribLocation);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
