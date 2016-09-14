#include "Game.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "Textbox.h"

#include <iostream>

void Game::init()
{
	Res::init();

	gary = NPC(Vector2f(100, 100), Vector2f(20, 20), "Edwin", 50);
	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	Weapon weapon = Weapon(10, 20, 5, wizard.position, "sword");
	wizard.hands[0] = weapon;
	text = Text(Vector2f(-20, -20), "lkllklk", Vector2f(5,5));
	text.setText("ththth");

	terrain = Terrain();
	terrain.addTerrain();

	gameTime = 0;

}

void Game::tick() {
	
	wizard.tick();
	wizard.hands[0].tick();
	Textbox::update();
	//Advance each animation
}


void Game::loop(float dt){

	if (gameTick) {
		tick();
	}

	gameTime += dt;

	WorldManager::checkWorld(wizard);

	Camera::position = wizard.position;
	Res::getShader("simpleShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("staticShader")->loadVector2f("cameraPosition", Camera::position);
	Res::getShader("terrainShader")->loadVector2f("cameraPosition", Camera::position);

	gary.update(dt);

}

void Game::render(){	
	
	//terrain.draw();
	//WorldManager::drawWorld();
	wizard.draw();
	//gary.draw();
	//text.draw();
	Textbox::draw();

}
