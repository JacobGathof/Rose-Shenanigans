#include "Res.h"
#include <iostream>


std::map<std::string, Model*> Res::models;
std::map<std::string, ShaderProgram*> Res::shaders;


Model * Res::getModel(std::string str)
{
	return models[str];
}

ShaderProgram * Res::getShader(std::string str)
{
	return shaders[str];
}

void Res::loadModel(std::string name, float * vertices, float * tex, int length){

	Model * model = ModelLoader::loadModel(vertices, tex, length);
	models[name] = model;
}

void Res::loadShader(std::string name, char * file_vertex, char * file_geo, char * file_fragment){
	ShaderProgram * program = new ShaderProgram;
	program->compileShader(file_vertex, file_geo, file_fragment);
	shaders[name] = program;
}

void Res::cleanResources(){
	for (auto m : models) {
		glDeleteVertexArrays(1, &m.second->VAO);
		delete m.second;
	}

	for (auto s : shaders) {
		glDeleteShader(s.second->shader_program);
		delete s.second;
	}
	std::cout << "Resources cleaned\n";

}

Res::Res()
{
}


Res::~Res()
{
}
