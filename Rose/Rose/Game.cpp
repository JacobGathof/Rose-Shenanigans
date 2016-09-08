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

	pro->loadFloat("height", .5f);
	pro->loadFloat("width", .5f);
	pro->loadSampler("image", 0);

	Res::loadTexture("Wizard", "Wizard.png");
	Res::getTexture("Wizard")->bind();

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0};
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1};

	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");

}

void Game::loop(){


}

void Game::render(){

	Model* m = Res::stdModel;
	m->bind();
	glDrawArrays(GL_TRIANGLES, 0, m->numberOfVertices);

}
