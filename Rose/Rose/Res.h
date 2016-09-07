#pragma once
#include <map>
#include "Model.h"
#include "ModelLoader.h"
#include "ShaderProgram.h"

class Res
{
private:

	static std::map<std::string, Model*> models;
	static std::map<std::string, ShaderProgram*> shaders;
	//static std::map<std::string, Texture*> textures;

public:

	static Model* getModel(std::string str);
	static ShaderProgram* getShader(std::string str);

	static void loadModel(std::string name, float * vertices, float * tex, int length);
	static void loadShader(std::string name, char* file_vertex, char* file_geo, char* file_fragment);

	static void cleanResources();

	Res();
	~Res();
};

