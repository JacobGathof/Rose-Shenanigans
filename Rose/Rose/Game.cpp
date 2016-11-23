#include "Game.h"
#include "Res.h"
#include "Camera.h"
#include "Player.h"
#include "Weapon.h"
#include "WorldManager.h"
#include "Vector2f.h"
#include "Renderer.h"
#include "Screen.h"
#include "Graph.h"
#include "Info.h"
#include <iostream>


void Game::init()
{
	Res::init();
	gameTime = 0;

	std::vector<Weapon> blank;

	player = Player(Vector2f(0, 0), Vector2f(32, 32), "Echo", 50);

	/*
	Dash skill = Dash();
	player.addSkill(1,skill);
	Weapon weapon = Weapon(10, 20, 5, player.position, 0, "sword");
	player.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	player.addMission(mission);
	*/

	Res::player = &player;
	Camera::setFocus(&player);
	Camera::setSpeed(1.0f);

	UIManager::statbox.player = &player;
	WorldManager::addToAllWorlds(&player);
	WorldManager::addPlayerToSlimes(&player);

	/*
	Graph graph = Graph();
	Info::x = 0;
	Graph::Node * buildHouse = new Graph::Node("Building a House", []() {return Info::x == 0; });
	Graph::Node * getMoney = new Graph::Node("Get Money", []() {return Info::x == 1; });
	Graph::Node * getBitches = new Graph::Node("Get Bitches", []() {return Info::x == 2; });
	Graph::Node * spaghetti = new Graph::Node("Mom's Spaghetti", []() {return Info::x == 3; });

	graph.addNode(buildHouse);
	graph.addNode(getMoney);
	graph.addNode(getBitches);
	graph.addNode(spaghetti);

	graph.connectNode(graph.currentNode, buildHouse);
	graph.connectNode(graph.currentNode, getMoney);
	graph.connectNode(graph.currentNode, getBitches);
	graph.connectNode(buildHouse, getMoney);
	graph.connectNode(getMoney, getBitches);
	graph.connectNode(getBitches, spaghetti);

	graph.printData();
	graph.update();
	graph.printData();
	Info::x = 1;
	graph.update();
	graph.printData();
	Info::x = 2;
	graph.update();
	graph.printData();
	Info::x = 3;
	graph.update();
	graph.printData();

	graph.destroy();
	*/

	/*
	std::cout << Info::PLAYER_STATUS << std::endl;
	Info::addPlayerStatus(BLEEDING);
	Info::addPlayerStatus(FIRE);
	std::cout << Info::PLAYER_STATUS << std::endl;
	Info::removePlayerStatus(BLEEDING);
	std::cout << Info::PLAYER_STATUS << std::endl;
	*/

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
