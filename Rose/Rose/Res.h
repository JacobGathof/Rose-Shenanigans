#pragma once
#include <map>
#include "Texture.h"
#include "Color.h"
#include "Text.h"

#define SCALEFACTOR 128.0

enum ShaderType {
	entityShader,
	particleShader,
	staticShader,
	textShader,
	terrainShader,
	uiShader,
	screenShader,
	lightShader
};


class Model;
class ModelLoader;
class ShaderProgram;
class Player;

class Res
{
private:
	static std::map<std::string, Model*> models;
	static std::map<ShaderType, ShaderProgram*> shaders;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Character*> characters;
	static std::map<std::string, GLuint> fbos;

	static void initShaders();
	static void initTextures();
	static void initModels();
	static void initFonts();
	static void initProjections();
	static void initManagers();
	static void initFramebuffers();

public:
	static Model * stdModel;
	static Player * player;

	static Model* getModel(std::string str);
	static ShaderProgram* getShader(ShaderType str);
	static Texture* getTexture(std::string str);
	static Character* getCharacter(std::string str);
	static GLuint getFramebuffer(std::string str);

	static void loadModel(std::string name, float * vertices, float * tex, int length);
	static void loadShader(ShaderType name, char* file_vertex, char* file_geo, char* file_fragment);
	static void loadTexture(std::string name, char* filename);
	static void loadTexture(std::string name, char* filename, int rows, int cols);
	static void loadFont(std::string name, char * filename_font, char* filename_texture);
	static void loadFBO(std::string fbo_name, std::string tex_name);

	static void updateShaders(float gameTime);

	static void resizeWindow(int width, int height);

	static void init();
	static void cleanResources();

};



class ShaderProgram
{
public:
	int shader_program;

	ShaderProgram();
	~ShaderProgram();

	void compileShader(char* file_vertex, char* file_geo, char* file_fragment);
	void use();

	void loadInteger(char* location, int value);
	void loadFloat(char* location, float value);
	void loadVector2f(char* location, Vector2f v);
	void loadMatrix(char* location, float * m);
	void loadColor(char* location, Color c);
	void loadSampler(char* location, int i);

private:

	void checkCompileErrors(int shader, char type);
	void checkLinkErrors(int shader);
	const char * getShaderSource(char* filename);

};



class ModelLoader{
public:

	static Model* loadModel(float* vertices, int length);
	static Model* loadModel(float* vertices, float* texCoords, int length);

	ModelLoader();
	~ModelLoader();

private:
	/*Attrib location in the Shaders, number of components per Vec, Pointer to data, size of data in bytes*/
	static void loadBuffer(int attribLocation, int size, float* data, int length);
};



class Model{
public:
	GLuint VAO;
	int numberOfVertices;
	void bind();

	/*Construct a Model Object with a VAO and the Number of Vertices to render*/
	Model(int vao, int num);
	Model();
	~Model();
};
