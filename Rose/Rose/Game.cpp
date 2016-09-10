#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include "Player.h"

#include <iostream>

void Game::init()
{
	world = World("start");
	
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

	world.AddEntity(&edwin);
	zone = LoadZones("second", 9, 9, Vector2f(55, 55));
	world.AddLoadZone(zone);
	worldmg = WorldManager(world);

	building = Building(Vector2f(.5, 0), "Inn", Vector2f(20, 20), Vector2f(.75, 0));
	world = World("second");
	world.AddObject(&building);
	worldmg.addWorld(world);
	gameTime = 0;

}

void Game::loop(float dt){

	gameTime += dt;

	if (((int)gameTime/2) % 2 == 0)
		edwin.move(Vector2f(1, 0), dt);
	else
		edwin.move(Vector2f(-1, 0), dt);

	worldmg.checkWorld(wizard);

}

void Game::render(){	
	
	worldmg.world.Draw();
	//edwin.draw();
	wizard.draw();
	//building.draw();

}
