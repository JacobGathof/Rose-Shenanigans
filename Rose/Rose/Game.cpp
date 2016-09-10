#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include "Player.h"
#include <iostream>

void Game::init()
{

	Res::loadShader("simpleShader", "simpleVertexShader.txt", 0, "simpleFragmentShader.txt");
	Res::loadShader("staticShader", "staticVertexShader.txt", 0, "staticFragmentShader.txt");

	ShaderProgram * pro = Res::getShader("simpleShader");
	pro->loadSampler("image", 0);

	Res::loadTexture("Echo", "Echo.png");
	
	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0};
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1};

	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");
	wizard = Player(100, 100, 100, 100, 50, Vector2f(0, 0), Vector2f(20, 20), "Echo", 20);

	//Res::loadTexture("Inn", "buildingtest.png");

	building = Building(Vector2f(.5, 0), "Inn", Vector2f(20, 20), Vector2f(.75, 0));

}

void Game::loop(){


}

void Game::render(){

	ShaderProgram * pro = Res::getShader("simpleShader");
	pro->loadFloat("animTimer", wizard.internalTime);
	pro->loadInteger("direction", wizard.direction);

	wizard.draw();
	building.draw();

}
