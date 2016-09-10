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

	Res::init();

	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 20);
	edwin = Entity(Vector2f(-30, 30), Vector2f(20, 20), "Edwin", 20);
	building = Building(Vector2f(.5, 0), "Inn", Vector2f(20, 20), Vector2f(.75, 0));
	text = Text(Vector2f(-20, -20), "I threw a wish in the well/I looked to you as it fell", Vector2f(5,5));
	

	world.AddEntity(&edwin);
	world.AddObject(&building);

	zone = LoadZone("second", 9, 9, Vector2f(55, 55));
	world.AddLoadZone(zone);
	worldmg = WorldManager(world);

	world = World("second");
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
	
	worldmg.world.draw();
	wizard.draw();
	text.draw();

}
