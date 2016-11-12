#include "Game.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "WorldManager.h"
#include "Vector2f.h"
#include <iostream>


void Game::init()
{
	Res::init();
	gameTime = 0;

	std::vector<Weapon> blank;

	player = Player(Vector2f(0, 0), Vector2f(32, 32), "Echo", 50);
	//player.numberOfAnimationRows = 1;
	//player.framesPerAnimation = 8;
	Dash skill = Dash();
	player.addSkill(1,skill);
	Weapon weapon = Weapon(10, 20, 5, player.position, "sword");
	player.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	player.addMission(mission);

	//mission = Mission(50, 50, blank, "hello", basicNPC);
	//player.addMission(mission);
	
	Res::player = &player;

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

	Camera::position = Vector2f(player.position.x + player.scale.x / 2, player.position.y + player.scale.y / 2);
	Res::updateShaders(gameTime);
	LightManager::updateLights(gameTime);

}

void Game::render(){

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("WorldFBO"));
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("LightFBO"));
	glClear(GL_COLOR_BUFFER_BIT);


	WorldManager::drawWorld();
	LightManager::drawLights();


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Res::getModel("ScreenVAO")->bind();
	Res::getShader(screenShader)->use();


	glActiveTexture(GL_TEXTURE0);
	Res::getTexture("WorldTexture")->bind();
	glActiveTexture(GL_TEXTURE1);
	Res::getTexture("LightTexture")->bind();

	glDrawArrays(GL_TRIANGLES, 0 ,6);

	glActiveTexture(GL_TEXTURE0);

	
	UIManager::textbox.draw();
	UIManager::statbox.draw();
	


}
