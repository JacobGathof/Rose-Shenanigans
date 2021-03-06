#pragma once
#include <map>
#include "Texture.h"
#include "Color.h"
#include "Text.h"

#define SCALEFACTOR 192.0f


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

enum TextureName{

	Light_Tex,
	Font,

	Echo_Tex,
	Mavis,
	Yuno,
	Lizbeth,
	Lucy,

	Slime_Tex,
	Rain,
	Inn,
	Edwin,
	Grass,
	Sword,
	Fire,
	Candle,
	Tree,
	Default,
	Textbox_Tex,
	Statbox_Tex,

	GreenSlime,
	FireSlime,
	SkySlime,
	Jibril_Tex,
	House,
	Inventory_Tex,

	Empty_skill,
	Dash_Tex,
	Bracket,


	WorldTexture,
	LightTexture,


};

enum Framebuffer {
	WorldFBO,
	LightFBO
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
	static std::map<TextureName, Texture*> textures;
	static std::map<std::string, Character*> characters;
	static std::map<Framebuffer, GLuint> fbos;

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
	static Texture* getTexture(TextureName name);
	static Character* getCharacter(std::string str);
	static GLuint getFramebuffer(Framebuffer name);

	static void loadModel(std::string name, float * vertices, float * tex, int length);
	static void loadShader(ShaderType name, char* file_vertex, char* file_geo, char* file_fragment);
	static void loadTexture(TextureName name, char* filename);
	static void loadTexture(TextureName name, char* filename, int rows, int cols);
	static void loadFont(TextureName name, char * filename_font, char* filename_texture);
	static void loadFBO(Framebuffer fbo_name, TextureName tex_name);

	static void updateShaders(float gameTime);

	static void resizeWindow(int width, int height);

	static void init();
	static void cleanResources();

};


/*
	ShaderProgram
	A class to contain the information about a single shader
	Used to compile shaders and load uniforms into them
*/
class ShaderProgram
{
public:
	/*Unique Shader ID assign by GL*/
	int shader_program;

	ShaderProgram();
	~ShaderProgram();

	/*Pass in Shader source files to compile. Vertex and Fragment files ar required, Geometry is optional*/
	void compileShader(char* file_vertex, char* file_geo, char* file_fragment);

	/*Bind as current Shader in use*/
	void use();

	/*Load uniform Integer at location*/
	void loadInteger(char* location, int value);
	/*Load uniform Float at location*/
	void loadFloat(char* location, float value);
	/*Load uniform Vector2f at location*/
	void loadVector2f(char* location, Vector2f v);
	/*Load uniform 4x4 float matrix at location*/
	void loadMatrix(char* location, float * m);
	/*Load uniform Color at location*/
	void loadColor(char* location, ColorRGB c);
	/*Load uniform Sampler at location (Interchangable with loadInteger)*/
	void loadSampler(char* location, int i);

private:

	void checkCompileErrors(int shader, char type);
	void checkLinkErrors(int shader);
	const char * getShaderSource(char* filename);

};


/*
	ModelLoader
	A static class which facilitates creating a Model object.
	Contains functions for compiling vertices and texture coordinates into data that GL can read
*/
class ModelLoader{
public:

	/*Load a basic Model, with only vertices*/
	static Model* loadModel(float* vertices, int length);

	/*Load a Model, with vertices and texture coordinates*/
	static Model* loadModel(float* vertices, float* texCoords, int length);

	ModelLoader();
	~ModelLoader();

private:
	/*Attrib location in the Shaders, number of components per Vec, Pointer to data, size of data in bytes*/
	static void loadBuffer(int attribLocation, int size, float* data, int length);
};




/*
	Model
	Represents a collection of vertices and texture coordinates
	When bound, any calls to GLDrawArrays(...) will render an instance of this Model
*/
class Model{
public:

	/*Number of vertices in the model*/
	int numberOfVertices;

	/*Bind this modelto be current*/
	void bind();

	/*Construct a Model Object with a VAO and the Number of Vertices to render*/
	Model(int vao, int num);
	Model();
	~Model();

private:
	/*Unique GL identifier for this Model*/
	GLuint VAO;

};
