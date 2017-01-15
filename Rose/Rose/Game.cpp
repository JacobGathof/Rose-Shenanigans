#include "Game.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "WorldManager.h"
#include "UI_Manager.h"
#include "Vector2f.h"
#include "Renderer.h"
#include "Screen.h"
#include "Graph.h"
#include "Info.h"
#include "Input.h"
#include "Timer.h"
#include <iostream>


void Game::init()
{
	Res::init();
	gameTime = 0;
	numberOfTicks = 0;
	state = FREE;

	std::vector<Weapon> blank;

	player = Player(Vector2f(0, 0), Vector2f(32, 32), "Echo", 50);

	
	//Dash skill = Dash();
	//player.addSkill(1,skill);
	//Weapon weapon = Weapon(10, 20, 5, player.position, 0, "sword");
	//player.hands[0] = weapon;
	//Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	//player.addMission(mission);
	

	Res::player = &player;
	Camera::setFocus(&player);
	Camera::setSpeed(2.0f);

	UIManager::statbox.player = &player;
	WorldManager::addToAllWorlds(&player);
	WorldManager::addPlayerToSlimes(&player);


}

void Game::tick() {


	numberOfTicks++;

	if (numberOfTicks >= 1) {
		numberOfTicks = 0;

		UIManager::update();

		WorldManager::tick();
		WorldManager::checkWorld(&player);
		WorldManager::checkEnemyCollisions(&player);

	}

}


void Game::loop(float dt){

	dt = Timer::dt;

	Input::processInput(dt);

	switch (state) {

		case GameState::MENU: loopMenu();  break;
		case GameState::INVENTORY: loopInventory(); break;
		case GameState::FREE: loopFree(dt); break;
		case GameState::LOCKED: break;

	}

}

void Game::render(){
	
	switch (state) {

		case GameState::MENU: renderMenu();  break;
		case GameState::INVENTORY: renderInventory(); break;
		case GameState::FREE: renderFree(); break;
		case GameState::LOCKED: break;

	}
}

void Game::renderMenu()
{
}

void Game::renderInventory()
{

	Renderer::prepareToRender();
	Renderer::render();
	Renderer::renderScreen();

	player.inventory.Display(player.hp, player.mana, player.exp, player.position);
	

}

void Game::renderFree()
{
	Renderer::prepareToRender();
	Renderer::render();
	Renderer::renderScreen();

	UIManager::textbox.draw();
	UIManager::statbox.draw();
	UIManager::skillbox.draw(&player);
	
}

void Game::renderPaused()
{
}



void Game::loopFree(float dt){

	if (Timer::tick) {
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

void Game::loopMenu()
{
}

void Game::loopInventory()
{


}

void Game::loopPaused()
{
}
