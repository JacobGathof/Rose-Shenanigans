#include "Res.h"
#include "WorldManager.h"
#include "LightManager.h"
#include "UIManager.h"
#include <iostream>
#include <string>
#include <sstream>

/*-----------------------------------------------------------------------

							*ResourceManager*

	A static class to hold all resources -> Models, Textures, Shaders.
	Res will include several helper classes to load resources, and
	the various static Managers, but will have no reference to other
	objects, making this class safe to include anywhere. 

	Almost all random crashes will be linked to this class somehow


------------------------------------------------------------------------*/



std::map<std::string, Model*> Res::models;
std::map<ShaderType, ShaderProgram*> Res::shaders;
std::map<std::string, Texture*> Res::textures;
std::map<std::string, Character*> Res::characters;

Model * Res::stdModel;



/*---------------------------------------
		RES Initialization
----------------------------------------*/

void Res::init() {
	
	initShaders();
	initProjections();
	initTextures();
	initFonts();
	initModels();
	initManagers();
}

void Res::initShaders(){
	Res::loadShader(entityShader, "simpleVertexShader.txt", 0, "simpleFragmentShader.txt");
	Res::loadShader(particleShader, "particleVertexShader.txt", 0, "particleFragmentShader.txt");
	Res::loadShader(staticShader, "staticVertexShader.txt", 0, "staticFragmentShader.txt");
	Res::loadShader(textShader, "textVertexShader.txt", 0, "textFragmentShader.txt");
	Res::loadShader(terrainShader, "terrainVertexShader.txt", 0, "terrainFragmentShader.txt");
	Res::loadShader(uiShader, "uiVertexShader.txt", 0, "uiFragmentShader.txt");
}

void Res::initTextures(){
	Res::loadTexture("Echo", "Echo.png");
	Res::loadTexture("Rain", "Rain.png");
	Res::loadTexture("Inn", "Echo.png");
	Res::loadTexture("Edwin", "Edwin.png");
	Res::loadTexture("Grass", "Grass.png");
	Res::loadTexture("sword", "sword.png");
	Res::loadTexture("Fire", "Fire.png");
	Res::loadTexture("Default", "Default.png");
}

void Res::initModels(){
	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };
	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");
}

void Res::initFonts(){
	Res::loadFont("Font", "Font.txt", "Font_Texture.png");
}

void Res::initProjections(){
	float projMat[] = { 1.0 / SCALEFACTOR, 0, 0, 0,		0, 1.0 / SCALEFACTOR, 0, 0,		0, 0, 2, -1,	0, 0, 0, 1 };
	Res::getShader(entityShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(particleShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(staticShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(textShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(terrainShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(uiShader)->loadMatrix("projectionMatrix", projMat);
}

void Res::initManagers(){
	WorldManager::init();
	UIManager::init();
}




/*---------------------------------------
		Getters and Loaders
----------------------------------------*/

Model * Res::getModel(std::string str)
{
	return models[str];
}

ShaderProgram * Res::getShader(ShaderType str)
{
	ShaderProgram * sp = shaders[str];
	sp->use();
	return sp;
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

/*---------------------------------------

	Destroy all contained resources;
	Call all other "Clean" methods

----------------------------------------*/

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
	UIManager::destroy();

	std::cout << "Resources cleaned\n";

}

void Res::resizeWindow(int width, int height) {
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