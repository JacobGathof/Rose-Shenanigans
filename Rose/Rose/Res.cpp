#include "Res.h"
#include "Textbox.h"
#include "WorldManager.h"
#include "LightManager.h"
#include <iostream>
#include <string>
#include <sstream>

std::map<std::string, Model*> Res::models;
std::map<ShaderType, ShaderProgram*> Res::shaders;
std::map<std::string, Texture*> Res::textures;
std::map<std::string, Character*> Res::characters;

Model * Res::stdModel;

void Res::init() {
	
	Res::loadShader(entityShader, "simpleVertexShader.txt", 0, "simpleFragmentShader.txt");
	Res::loadShader(particleShader, "particleVertexShader.txt", 0, "particleFragmentShader.txt");
	Res::loadShader(staticShader, "staticVertexShader.txt", 0, "staticFragmentShader.txt");
	Res::loadShader(textShader, "textVertexShader.txt", 0, "textFragmentShader.txt");
	Res::loadShader(terrainShader, "terrainVertexShader.txt", 0, "terrainFragmentShader.txt");
	Res::loadShader(uiShader, "uiVertexShader.txt", 0, "uiFragmentShader.txt");

	//float scaleFactor = 128.0;
	float projMat[] = { 1.0 / SCALEFACTOR, 0, 0, 0,			0, 1.0 / SCALEFACTOR, 0, 0,			0, 0, 2, -1,		0, 0, 0, 1 };

	Res::getShader(entityShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(particleShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(staticShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(textShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(terrainShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(uiShader)->loadMatrix("projectionMatrix", projMat);

	Res::loadTexture("Echo", "Echo.png");
	Res::loadTexture("Rain", "Rain.png");
	Res::loadTexture("Inn", "Echo.png");
	Res::loadTexture("Edwin", "Edwin.png");
	Res::loadTexture("Grass", "Grass.png");
	Res::loadTexture("sword", "sword.png");
	Res::loadTexture("Fire", "Fire.png");

	Res::loadFont("Font", "Font.txt", "Font_Texture.png");

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };
	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");

	WorldManager::init();
	Textbox::init();
}

Model * Res::getModel(std::string str)
{
	return models[str];
	if (models.find(str) == models.end()) {
		std::cout << "Could not get Model" << std::endl;
	}
}

ShaderProgram * Res::getShader(ShaderType str)
{
	if (shaders.find(str) == shaders.end()) {
		std::cout << "Could not get Shader" << std::endl;
	}
	ShaderProgram * sp = shaders[str];
	sp->use();
	return sp;
}

Texture * Res::getTexture(std::string str)
{
	if (textures.find(str) == textures.end()) {
		std::cout << "Could not get Texture" << std::endl;
	}
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

void Res::loadShader(ShaderType name, char * file_vertex, char * file_geo, char * file_fragment){
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

	WorldManager::destroy();
	Textbox::destroy();
	//LightManager::cleanUp();

	std::cout << "Resources cleaned\n";

}

void Res::window_resize_callback(int width, int height) {
	int size;
	int offy = 0;
	int offx = 0;

	// makes the viewport always square and always centered in window
	if (width > height) {
		size = height;
		offx = (width - height) / 2;
	}
	else {
		size = width;
		offy = (height - width) / 2;
	}
	glViewport(offx, offy, size, size);

	if (0) {
		// keeps sizes the same when changing window size: make window bigger, people stay same size 
		float projMat[] = { 1.0 / (SCALEFACTOR*size / 800.0), 0, 0, 0,			0, 1.0 / (SCALEFACTOR*size / 800.0), 0, 0,			0, 0, 2, -1,		0, 0, 0, 1 };

		Res::getShader(entityShader)->loadMatrix("projectionMatrix", projMat);
		Res::getShader(particleShader)->loadMatrix("projectionMatrix", projMat);
		Res::getShader(staticShader)->loadMatrix("projectionMatrix", projMat);
		Res::getShader(textShader)->loadMatrix("projectionMatrix", projMat);
		Res::getShader(terrainShader)->loadMatrix("projectionMatrix", projMat);
		Res::getShader(uiShader)->loadMatrix("projectionMatrix", projMat);
	}
	else {
		// scales image size to window size: make window bigger, make people bigger
	}
}


Res::Res()
{
}


Res::~Res()
{
}
