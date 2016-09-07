#include "Res.h"
#include <iostream>


std::map<std::string, Model*> Res::models;
std::map<std::string, ShaderProgram*> Res::shaders;
std::map<std::string, Texture*> Res::textures;

Model * Res::stdModel;


Model * Res::getModel(std::string str)
{
	return models[str];
}

ShaderProgram * Res::getShader(std::string str)
{
	return shaders[str];
}

Texture * Res::getTexture(std::string str)
{
	return textures[str];
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

void Res::loadTexture(std::string name, char * filename){
	Texture * t = new Texture(filename);
	textures[name] = t;
}

void Res::cleanResources(){
	for (auto m : models) {
		delete m.second;
	}

	for (auto s : shaders) {
		delete s.second;
	}

	for (auto t : textures) {
		delete t.second;
	}
	std::cout << "Resources cleaned\n";

}

Res::Res()
{
}


Res::~Res()
{
}
