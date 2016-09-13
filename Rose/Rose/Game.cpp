#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"

#include <iostream>

void Game::init()
{
	Res::init();

	gary = NPC(Vector2f(100, 100), Vector2f(20, 20), "Edwin", 50);
	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	text = Text(Vector2f(-20, -20), "I threw a wish in the well/Don't ask me I'll never tell", Vector2f(5,5));
	text.setText("I looked to you as it fell/And now you're in my way");

	terrain = Terrain();
	terrain.addTerrain();

	gameTime = 0;

}

void Game::loop(float dt){

	gameTime += dt;

	WorldManager::checkWorld(wizard);

	Camera::position = wizard.position;
	Res::getShader("simpleShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("staticShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("terrainShader")->loadVector2f("cameraPosition", Camera::position);
}

void Game::render(){	
	
	//terrain.draw();
	WorldManager::drawWorld();
	wizard.draw();
	gary.draw();
	//text.draw();

}
