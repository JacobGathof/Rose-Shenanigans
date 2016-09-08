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
	pro->loadSampler("image", 0);

	Res::loadTexture("Wizard", "Wizard.png");

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0};
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1};

	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");

	wizard = Object(Vector2f(0, 0), Vector2f(1, 1), "Wizard");


}

void Game::loop(){


}

void Game::render(){

	wizard.draw();

}
