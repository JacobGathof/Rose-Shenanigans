#include "Game.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "Textbox.h"
#include "WorldManager.h"
#include "Vector2f.h"
#include <iostream>


void Game::init()
{
	Res::init();
	gameTime = 0;


	std::vector<Weapon> blank;

	player = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	player.framesPerAnimation = 1;
	player.numberOfAnimationRows = 1;
	Weapon weapon = Weapon(10, 20, 5, player.position, "sword");
	player.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	player.addMission(mission);

	//mission = Mission(50, 50, blank, "hello", basicNPC);
	//player.addMission(mission);
	


	circleVector = Vector2f(1, 0);
	UIManager::statbox.player = &player;
	WorldManager::addToAllWorlds(&player);


}

void Game::tick() {

	player.tick();
	player.hands[0].tick();
	UIManager::update();

	WorldManager::tick();
	WorldManager::checkWorld(&player);

}


void Game::loop(float dt){

	if (gameTick) {
		tick();
		gameTick = false;
	}

	circleVector = Vector2f(cos(gameTime), sin(gameTime));

	WorldManager::update(dt);

	gameTime += dt;

	Camera::position = Vector2f(player.position.x + player.scale.x / 2, player.position.y + player.scale.y / 2);
	Res::updateShaders(gameTime);

}

void Game::render(){

	WorldManager::drawWorld();
	UIManager::textbox.draw();
	UIManager::statbox.draw();
	Res::getShader(uiShader)->loadInteger("doTexture", 1);
	Res::getTexture("Grass")->bind();
	UIManager::tilebox.draw();
	Res::getShader(uiShader)->loadInteger("doTexture", 0);

}
