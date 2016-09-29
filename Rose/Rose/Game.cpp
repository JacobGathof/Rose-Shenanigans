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
#include "UIManager.h"
#include "Vector2f.h"
#include <iostream>


void Game::init()
{
	Res::init();
	std::vector<Weapon> blank;
	basicNPC = NPC(Vector2f(10, -10), Vector2f(20, 20), "Edwin", 50);
	basicNPC.numberOfAnimationRows = 4;

	player = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	Weapon weapon = Weapon(10, 20, 5, player.position, "sword");
	player.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	player.addMission(mission);
	mission = Mission(50, 50, blank, "hello", basicNPC);
	player.addMission(mission);
	gameTime = 0;

	circleVector = Vector2f(1, 0);

	UIManager::statbox.player = &player;


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
	}

	circleVector = Vector2f(cos(gameTime), sin(gameTime));

	WorldManager::update(dt);

	gameTime += dt;

	Camera::position = Vector2f(player.position.x + player.scale.x / 2, player.position.y + player.scale.y / 2);
	Res::updateShaders(gameTime);

	if ((player.position^basicNPC.position) <= 2.0f && !UIManager::textbox.isVisible) {
		basicNPC.trigger();
	}

	basicNPC.update(dt);
}

void Game::render(){

	WorldManager::drawWorld();
	basicNPC.draw();
	player.draw();
	UIManager::textbox.draw();
	UIManager::statbox.draw();

}
