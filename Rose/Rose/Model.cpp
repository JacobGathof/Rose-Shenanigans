#include "Model.h"



void Model::bind(){
	glBindVertexArray(VAO);
}

Model::Model(int vao, int num)
{
	this->VAO = vao;
	this->numberOfVertices = num;
}

Model::Model()
{
}


Model::~Model(){
	glDeleteVertexArrays(1, &VAO);
}
