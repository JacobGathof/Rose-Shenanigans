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

#include <iostream>

void Game::init()
{
	Res::init();
	std::vector<Weapon> blank;
	gary = NPC(Vector2f(10, 10), Vector2f(20, 20), "Edwin", 50);
	gary.numberOfAnimationRows = 4;

	wizard = Player(Vector2f(0, 0), Vector2f(20, 20), "Echo", 50);
	Weapon weapon = Weapon(10, 20, 5, wizard.position, "sword");
	wizard.hands[0] = weapon;
	Mission mission = Mission(50, 50, blank, "hello", Vector2f(64, 64));
	wizard.addMission(mission);
	mission = Mission(50, 50, blank, "hello", gary);
	wizard.addMission(mission);
	gameTime = 0;

	circleVector = Vector2f(1, 0);


	/*
	gary.addAction(NPCAction(WAIT));
	gary.addAction(NPCAction(TALK, "Follow Me"));
	gary.addAction(NPCAction(WAIT));
	gary.addAction(NPCAction(MOVE, Vector2f(50, 20)));
	gary.addAction(NPCAction(WAIT));
	gary.addAction(NPCAction(MOVE, Vector2f(300,20)));
	gary.addAction(NPCAction(MOVE, Vector2f(100, 50)));
	gary.addAction(NPCAction(WAIT));
	gary.addAction(NPCAction(TALK, "It's dangerous to go alone."));
	gary.addAction(NPCAction(TALK, "Take this"));
	gary.addAction(NPCAction(WAIT));
	gary.addAction(NPCAction(MOVE, Vector2f(0, 0)));
	gary.addAction(NPCAction(MOVE_SPECIAL, &circleVector));
	*/
}

void Game::tick() {
	
	wizard.tick();
	wizard.hands[0].tick();
	UIManager::update();

	WorldManager::tick();
	WorldManager::checkWorld(&wizard);

}


void Game::loop(float dt){

	if (gameTick) {
		tick();
	}

	circleVector = Vector2f(cos(gameTime), sin(gameTime));

	WorldManager::update(dt);

	gameTime += dt;

	Camera::position = Vector2f(wizard.position.x + wizard.scale.x / 2, wizard.position.y + wizard.scale.y / 2);
	Res::getShader(entityShader)->loadVector2f("cameraPosition", Camera::position);
	Res::getShader(staticShader)->loadVector2f("cameraPosition", Camera::position);
	Res::getShader(terrainShader)->loadVector2f("cameraPosition", Camera::position);
	Res::getShader(particleShader)->loadVector2f("cameraPosition", Camera::position);

	Res::getShader(entityShader)->loadFloat("gameTime", gameTime);

	if (Vector2f::distance(wizard.position, gary.position) <= 2.0f && !UIManager::textbox.isVisible) {
		gary.trigger();
	}

	gary.update(dt);
}

void Game::render(){	

	WorldManager::drawWorld();
	gary.draw();
	wizard.draw();
	UIManager::textbox.draw();
	box.draw();

}
