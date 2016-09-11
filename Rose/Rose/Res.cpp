#include "Res.h"
#include <iostream>
#include <string>
#include <sstream>


std::map<std::string, Model*> Res::models;
std::map<std::string, ShaderProgram*> Res::shaders;
std::map<std::string, Texture*> Res::textures;
std::map<std::string, Character*> Res::characters;

Model * Res::stdModel;

void Res::init() {

	Res::loadShader("simpleShader", "simpleVertexShader.txt", 0, "simpleFragmentShader.txt");
	Res::loadShader("staticShader", "staticVertexShader.txt", 0, "staticFragmentShader.txt");
	Res::loadShader("textShader", "textVertexShader.txt", 0, "textFragmentShader.txt");
	Res::loadShader("terrainShader", "terrainVertexShader.txt", 0, "terrainFragmentShader.txt");

	Res::loadTexture("Echo", "Echo.png");
	Res::loadTexture("Inn", "Echo.png");
	Res::loadTexture("Edwin", "Edwin.png");
	Res::loadTexture("Grass", "Grass.png");

	Res::loadFont("Font", "Font.txt", "Font_Texture.png");


	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };
	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");

}

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

Character * Res::getCharacter(std::string str)
{
	return characters[str];
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

void Res::loadFont(std::string name, char * filename_font, char* filename_texture)
{
	loadTexture(name, filename_texture);

	std::ifstream file;
	file.open(filename_font, file.in | file.binary);
	std::string str;

	char buffer[512];
	char item[64];

	for (int i = 0; i < 4; i++) {
		file.ignore(512, '\n');
	}

	while (!file.eof()) {

		std::stringstream line;
		std::vector<int> elements;

		file.getline(buffer, 512);
		if (buffer[0] == 'k') break;
		line << buffer;

		line.ignore(7);
		while (!line.eof()) {

			line.getline(item, 64, '=');
			if (item[0] == '\0') continue;

			str.assign(item);
			str = str.substr(0, str.find(" "));

			elements.push_back(std::stoi(str));

		}


		Character * ch = new Character(elements);
		std::string str("");
		str += (char)(elements[0]);

		characters[str] = ch;

	}

	file.close();

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

	for (auto c : characters) {
		delete c.second;
	}

	std::cout << "Resources cleaned\n";

}


Res::Res()
{
}


Res::~Res()
{
}
