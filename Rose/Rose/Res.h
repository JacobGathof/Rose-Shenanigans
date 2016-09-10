#pragma once
#include <map>
#include "Model.h"
#include "ModelLoader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Character.h"

class Res
{
private:
	static std::map<std::string, Model*> models;
	static std::map<std::string, ShaderProgram*> shaders;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Character*> characters;

public:
	static Model * stdModel;

	static Model* getModel(std::string str);
	static ShaderProgram* getShader(std::string str);
	static Texture* getTexture(std::string str);
	static Character* getCharacter(std::string str);

	static void loadModel(std::string name, float * vertices, float * tex, int length);
	static void loadShader(std::string name, char* file_vertex, char* file_geo, char* file_fragment);
	static void loadTexture(std::string name, char* filename);
	static void loadFont(std::string name, char * filename_font, char* filename_texture);

	static void init();
	static void cleanResources();

	Res();
	~Res();
};

