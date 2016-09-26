#pragma once
#include <map>
#include "ModelLoader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Character.h"

#define SCALEFACTOR 96.0

enum ShaderType {
	entityShader,
	particleShader,
	staticShader,
	textShader,
	terrainShader,
	uiShader
};

class Res
{
private:
	static std::map<std::string, Model*> models;
	static std::map<ShaderType, ShaderProgram*> shaders;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Character*> characters;

public:
	static Model * stdModel;

	static Model* getModel(std::string str);
	static ShaderProgram* getShader(ShaderType str);
	static Texture* getTexture(std::string str);
	static Character* getCharacter(std::string str);

	static void loadModel(std::string name, float * vertices, float * tex, int length);
	static void loadShader(ShaderType name, char* file_vertex, char* file_geo, char* file_fragment);
	static void loadTexture(std::string name, char* filename);
	static void loadFont(std::string name, char * filename_font, char* filename_texture);

	static void window_resize_callback(int width, int height);

	static void init();
	static void cleanResources();

	Res();
	~Res();
};

