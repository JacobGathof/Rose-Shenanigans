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
	Res::loadTexture("Inn", "Echo.png");
	Res::loadTexture("Edwin", "Edwin.png");
	
	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0};
	float tex[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1};

	Res::loadModel("Square", vertices, tex, 12);
	Res::stdModel = Res::getModel("Square");

	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 20);
	edwin = Entity(Vector2f(-30, 30), Vector2f(20, 20), "Edwin", 20);

	building = Building(Vector2f(.5, 0), "Inn", Vector2f(20, 20), Vector2f(.75, 0));

	gameTime = 0;

}

void Game::loop(float dt){

	gameTime += dt;

	if (((int)gameTime/2) % 2 == 0)
		edwin.move(Vector2f(1, 0), dt);
	else
		edwin.move(Vector2f(-1, 0), dt);



}

void Game::render(){	

	edwin.draw();
	wizard.draw();
	building.draw();

}
