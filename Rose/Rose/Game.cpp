#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "Textbox.h"
#include "LightManager.h"

#include <iostream>

void Game::init()
{
	Res::init();
	
	gary = NPC(Vector2f(10, 10), Vector2f(20, 20), "Edwin", 50);
	gary.numberOfAnimationRows = 4;

	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	Weapon weapon = Weapon(10, 20, 5, wizard.position, "sword");
	wizard.hands[0] = weapon;

	//terrain = Terrain();
	//terrain.addTerrain();

	gameTime = 0;

}

void Game::tick() {
	
	wizard.tick();
	wizard.hands[0].tick();
	Textbox::update();

	WorldManager::tick();
	WorldManager::checkWorld(&wizard);

}


void Game::loop(float dt){

	if (gameTick) {
		tick();
	}

	WorldManager::update(dt);

	gameTime += dt;

	Camera::position = wizard.position;
	Res::getShader("entityShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("staticShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("terrainShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("particleShader")->loadVector2f("cameraPosition", Camera::position);

	Res::getShader("entityShader")->loadFloat("gameTime", gameTime);
	gary.update(dt);

}

void Game::render(){	

	WorldManager::drawWorld();
	gary.draw();
	wizard.draw();
	Textbox::draw();

}
