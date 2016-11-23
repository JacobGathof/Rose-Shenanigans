#include "Res.h"
#include "WorldManager.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <sstream>


#pragma region RES
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
std::map<std::string, GLuint> Res::fbos;

Model * Res::stdModel;
Player * Res::player;



/*---------------------------------------
		RES Initialization
----------------------------------------*/


void Res::updateShaders(float gameTime){
	getShader(entityShader)->loadVector2f("cameraPosition", Camera::position);
	getShader(staticShader)->loadVector2f("cameraPosition", Camera::position);
	getShader(terrainShader)->loadVector2f("cameraPosition", Camera::position);
	getShader(particleShader)->loadVector2f("cameraPosition", Camera::position);
	getShader(lightShader)->loadVector2f("cameraPosition", Camera::position);

	Res::getShader(entityShader)->loadFloat("gameTime", gameTime);
}

void Res::init() {
	
	initShaders();
	initProjections();
	initTextures();
	initFonts();
	initModels();
	initManagers();
	initFramebuffers();
}

void Res::initShaders(){
	Res::loadShader(entityShader, "Resources/simpleVertexShader.txt", 0, "Resources/simpleFragmentShader.txt");
	Res::loadShader(particleShader, "Resources/particleVertexShader.txt", 0, "Resources/particleFragmentShader.txt");
	Res::loadShader(staticShader, "Resources/staticVertexShader.txt", 0, "Resources/staticFragmentShader.txt");
	Res::loadShader(textShader, "Resources/textVertexShader.txt", 0, "Resources/textFragmentShader.txt");
	Res::loadShader(terrainShader, "Resources/terrainVertexShader.txt", 0, "Resources/terrainFragmentShader.txt");
	Res::loadShader(uiShader, "Resources/uiVertexShader.txt", 0, "Resources/uiFragmentShader.txt");
	Res::loadShader(screenShader, "Resources/screenVertexShader.txt", 0, "Resources/screenFragmentShader.txt");
	Res::loadShader(lightShader, "Resources/lightVertexShader.txt", 0, "Resources/lightFragmentShader.txt");
}

void Res::initTextures(){

	Res::loadTexture("Echo", "Resources/Echo.png", 5, 3);
	Res::loadTexture("Slime", "Resources/Slime.png", 9, 9);
	Res::loadTexture("Rain", "Resources/Rain.png", 5, 3);
	Res::loadTexture("Inn", "Resources/Echo.png");
	Res::loadTexture("Edwin", "Resources/Edwin.png", 4, 3);
	Res::loadTexture("Grass", "Resources/terrainTiles.png");
	//Res::loadTexture("Grass", "Resources/Grass.png");
	Res::loadTexture("sword", "Resources/sword.png");
	Res::loadTexture("Fire", "Resources/Fire.png");
	Res::loadTexture("Candle", "Resources/Sprites.png");
	Res::loadTexture("Tree", "Resources/Tree.png");
	Res::loadTexture("Default", "Resources/Default.png");
	Res::loadTexture("Light", "Resources/lightTex.png");
	Res::loadTexture("Textbox", "Resources/Textbox.png");
	Res::loadTexture("Statbox", "Resources/Statbox.png");

	Res::loadTexture("GreenSlime", "Resources/GreenSlime.png", 1, 8);
	Res::loadTexture("FireSlime", "Resources/FireSlime.png", 1, 8);
	Res::loadTexture("SkySlime", "Resources/SkySlime.png", 1, 8);
	//Res::loadTexture("Jibril", "Resources/Jibril.png", 1, 1);
	Res::loadTexture("Jibril", "Resources/Rose.png", 1, 4);
	Res::loadTexture("House", "Resources/CarpenterHouse.png");

	//skill textures
	Res::loadTexture("empty_skill", "Resources/empty_skill.png");
	Res::loadTexture("dash", "Resources/dash.png");
	Res::loadTexture("bracket", "Resources/bracket.png");
}

void Res::initModels(){
	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };
	Res::loadModel("Square", vertices, tex, 12);

	float vertices_[] = { -1,-1, -1,1, 1,1 , 1,1, 1,-1, -1,-1 };
	float tex_[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };
	Res::loadModel("ScreenVAO", vertices_, tex_, 12);

	Res::loadModel("CenteredModel", vertices_, tex_, 12);


	Res::stdModel = Res::getModel("Square");
}

void Res::initFonts(){
	Res::loadFont("Font", "Resources/Font.txt", "Resources/Font_Texture.png");
}

void Res::initProjections(){
	float projMat[] = { 1.0 / SCALEFACTOR, 0, 0, 0,		0, 1.0 / SCALEFACTOR, 0, 0,		0, 0, 2, -1,	0, 0, 0, 1 };
	Res::getShader(entityShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(particleShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(staticShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(textShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(terrainShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(uiShader)->loadMatrix("projectionMatrix", projMat);
	Res::getShader(lightShader)->loadMatrix("projectionMatrix", projMat);
}

void Res::initManagers(){
	WorldManager::init();
	UIManager::init();
	NPCManager::init();
}

void Res::initFramebuffers(){
	Res::loadFBO("WorldFBO","WorldTexture");
	Res::loadFBO("LightFBO", "LightTexture");

	Res::getShader(screenShader)->loadInteger("world", 0);
	Res::getShader(screenShader)->loadInteger("lights", 1);

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

GLuint Res::getFramebuffer(std::string str)
{
	return fbos[str];
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

void Res::loadTexture(std::string name, char * filename, int rows, int cols) {
	Texture * t = new Texture(filename, rows, cols);
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

void Res::loadFBO(std::string fbo_name, std::string tex_name){

	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	/*
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	*/


	if (!glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer failed";


	fbos[fbo_name] = fbo;
	textures[tex_name] = new Texture(texture);

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
	NPCManager::destroy();

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

#pragma endregion


#pragma region MODELLOADER

Model * ModelLoader::loadModel(float * vertices, int length) {

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	loadBuffer(0, 2, vertices, length);

	Model * m = new Model(VAO, length);
	return m;
}

Model * ModelLoader::loadModel(float * vertices, float * texCoords, int length)
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	loadBuffer(0, 2, vertices, length);
	loadBuffer(1, 2, texCoords, length);

	Model * m = new Model(VAO, length / 2);
	return m;
}

ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

void ModelLoader::loadBuffer(int attribLocation, int size, float * data, int length) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, length * 4, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribLocation, size, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(attribLocation);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#pragma endregion


#pragma region MODEL

void Model::bind() {
	glBindVertexArray(VAO);
}

Model::Model(int vao, int num)
{
	this->VAO = vao;
	this->numberOfVertices = num;
}

Model::Model()
{
}


Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
}

#pragma endregion


#pragma region SHADERPROGRAM


void ShaderProgram::compileShader(char * file_vertex, char * file_geo, char * file_fragment)
{

	shader_program = glCreateProgram();

	int shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* source_vertex = getShaderSource(file_vertex);
	glShaderSource(shader_vertex, 1, &source_vertex, 0);
	glCompileShader(shader_vertex);
	glAttachShader(shader_program, shader_vertex);
	delete[] source_vertex;

	if (file_geo != NULL) {
		int shader_geometry = glCreateShader(GL_GEOMETRY_SHADER);
		const char* source_geometry = getShaderSource(file_geo);
		glShaderSource(shader_geometry, 1, &source_geometry, 0);
		glCompileShader(shader_geometry);
		glAttachShader(shader_program, shader_geometry);

		checkCompileErrors(shader_geometry, 'g');
		delete[] source_geometry;
	}


	int shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* source_fragment = getShaderSource(file_fragment);
	glShaderSource(shader_fragment, 1, &source_fragment, 0);
	glCompileShader(shader_fragment);
	glAttachShader(shader_program, shader_fragment);
	delete[] source_fragment;


	checkCompileErrors(shader_vertex, 'v');
	checkCompileErrors(shader_fragment, 'f');


	glLinkProgram(shader_program);
	checkLinkErrors(shader_program);
	glUseProgram(shader_program);

}

void ShaderProgram::use()
{
	glUseProgram(this->shader_program);
}

void ShaderProgram::checkCompileErrors(int shader, char type)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infolog[2048];
		glGetShaderInfoLog(shader, 2048, 0, infolog);
		std::cout << "Shader : " << ((type == 'v') ? "Vertex Shader" : (type == 'f') ? "Fragment Shader" : "Geometry Shader") << "\n";
		std::cout << infolog << std::endl;
		std::cout << "--------------------\n";
	}

}

void ShaderProgram::checkLinkErrors(int program)
{
	int success;
	glGetShaderiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		char infolog[2048];
		glGetShaderInfoLog(program, 2048, 0, infolog);
		std::cout << "Program Link Errors\n";
		std::cout << infolog << std::endl;
	}

}

const char* ShaderProgram::getShaderSource(char * filename)
{

	std::ifstream file;
	file.open(filename, file.binary | file.in);

	char *buffer;
	int size;

	file.seekg(0, file.end);
	size = file.tellg();
	file.seekg(0, file.beg);

	buffer = new char[size + 1];
	file.read(buffer, size);

	buffer[size] = '\0';

	return buffer;

}

void ShaderProgram::loadInteger(char * location, int value) {
	glUniform1i(glGetUniformLocation(this->shader_program, location), value);
}

void ShaderProgram::loadFloat(char * location, float value) {
	glUniform1f(glGetUniformLocation(this->shader_program, location), value);
}

void ShaderProgram::loadVector2f(char * location, Vector2f v) {
	glUniform2f(glGetUniformLocation(this->shader_program, location), v.x, v.y);
}

void ShaderProgram::loadMatrix(char * location, float * m) {
	glUniformMatrix4fv(glGetUniformLocation(this->shader_program, location), 1, true, m);
}

void ShaderProgram::loadColor(char * location, Color c) {
	glUniform3f(glGetUniformLocation(this->shader_program, location), c.r, c.g, c.b);
}

void ShaderProgram::loadSampler(char * location, int i) {
	glUniform1i(glGetUniformLocation(this->shader_program, location), i);
}

ShaderProgram::~ShaderProgram() {

	glDeleteShader(shader_program);
}

ShaderProgram::ShaderProgram() {
}

#pragma endregion


