#pragma once

#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Vector2f.h"
#include "Color.h"

class ShaderProgram
{
public:
	int shader_program;

	ShaderProgram();
	~ShaderProgram();

	/*Take in three file names (or NULL) to create a shader program with vertex, geometry, and fragment components*/
	void compileShader(char* file_vertex, char* file_geo, char* file_fragment);

	/*Bind this ShaderProgram*/
	void use();

	/*Load an integer uniform to the shader at a specified location (uniform name)*/
	void loadInteger(char* location, int value);

	/*Load a float uniform to the shader at a specified location (uniform name)*/
	void loadFloat(char* location, float value);

	void loadVector2f(char* location, Vector2f v);
	void loadColor(char* location, Color c);
	
	/*Load a sampler uniform to the shader at a specified location. Identical to loading an integer*/
	void loadSampler(char* location, int i);

private:

	/*Checks and prints any errors in the compilation of shaders*/
	void checkCompileErrors(int shader);

	/*Checks and prints any errors in the linking of shaders*/
	void checkLinkErrors(int shader);

	/*Return the char* representing the shader source. Converts file into usable char buffer*/
	const char * getShaderSource(char* filename);

};