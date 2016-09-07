#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include <iostream>

void Game::init()
{

	Res::loadShader("simpleShader", "simpleVertexShader.txt", 0, "simpleFragmentShader.txt");
	ShaderProgram * pro = Res::getShader("simpleShader");

	pro->loadFloat("height", 1);
	pro->loadFloat("width", 1);

	float vertices[] = { 0,0, 0,1, 1,1 };
	float tex[] = { 0,0, 0,1, 1,1 };

	Res::loadModel("Triangle", vertices, tex, 6);

}

void Game::loop(){


}

void Game::render(){

	Model* m = Res::getModel("Triangle");

	glBindVertexArray(m->VAO);
	glDrawArrays(GL_TRIANGLES, 0, m->numberOfVertices);

}
