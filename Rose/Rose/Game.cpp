#include "Game.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "WorldManager.h"
#include "Vector2f.h"
#include "Renderer.h"
#include "Screen.h"
#include <iostream>


void Game::init()
{
	Res::init();
	gameTime = 0;

	std::vector<Weapon> blank;

	player = Player(Vector2f(0, 0), Vector2f(32, 32), "Echo", 50);

	Dash skill = Dash();
	player.addSkill(1,skill);
	Weapon weapon = Weapon(10, 20, 5, player.position, 0, "sword");
	player.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	player.addMission(mission);


	
	Res::player = &player;
	Camera::setFocus(&player);
	Camera::setSpeed(1.0f);

	UIManager::statbox.player = &player;
	WorldManager::addToAllWorlds(&player);
	WorldManager::addPlayerToSlimes(&player);

}

void Game::tick() {

	UIManager::update();

	WorldManager::tick();
	WorldManager::checkWorld(&player);
	WorldManager::checkEnemyCollisions(&player);

}


void Game::loop(float dt){

	if (gameTick) {
		tick();
		gameTick = false;
	}

	WorldManager::update(dt);

	gameTime += dt;

	Screen::update(dt);
	Camera::update(dt);
	Res::updateShaders(gameTime);
	LightManager::updateLights(gameTime);

}

void Game::render(){


	
	Renderer::prepareToRender();
	Renderer::render();
	Renderer::renderScreen();

	

	
	UIManager::textbox.draw();
	UIManager::statbox.draw();
	UIManager::skillbox.draw(&player);

}
