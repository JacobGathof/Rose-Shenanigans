#include "Input.h"
#include "UI_Manager.h"
#include "WorldManager.h"
#include <iostream>
#include "Screen.h"
#include "Menu.h"
#include "opengl-wrapper\SFML\include\SFML\Window.hpp"

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;
int Input::tilePointer;
int Input::lastFive[];
bool Input::testVar = false;


void Input::processInput(float dt)
{

	switch (game->state) {

		case GameState::MENU: MenuLogic();  break;
		case GameState::INVENTORY: InventoryLogic(); break;
		case GameState::FREE: GameLogic(dt); break;
		case GameState::LOCKED: LockedLogic(); break;

	}

	
	if (keys[sf::Keyboard::T]) {
		keys[sf::Keyboard::T] = false;
		if (!UIManager::textbox.currentlyWriting) {
			UIManager::textbox.advanceQueue();
		}
	}

	/*
	if (lastFive[0] == 83 && lastFive[1] == 65 && lastFive[2] == 78 && lastFive[3] == 73 && lastFive[4] == 67) {
		game->player.speed *= 2;
		lastFive[0] = 0;
	}
	*/
}

void Input::turnKeyOn(int key){
	if (keys[key]) return;
	keys[key] = true;
	for (int i = 1; i < 5; i++) {
		lastFive[i - 1] = lastFive[i];
	}
	lastFive[4] = key;
}

NPC* Input::findClosestNPC(Vector2f position){
	return WorldManager::currentWorld->findClosestNPC(position);
}

void Input::MenuLogic(){

	if (keys[sf::Keyboard::W]) {
		keys[sf::Keyboard::W] = false;
		Menu::setSelectedIndex(-1);
	}

	if (keys[sf::Keyboard::S]) {
		keys[sf::Keyboard::S] = false;
		Menu::setSelectedIndex(1);
	}

	if (keys[sf::Keyboard::Space]) {
		keys[sf::Keyboard::Space] = false;
		Menu::actOnSelection();
	}


}

void Input::GameLogic(float dt){

	Vector2f movement;
	if (keys[sf::Keyboard::W] || keys[sf::Keyboard::Up]) {
		movement = movement + Vector2f(0, 1);
	}
	if (keys[sf::Keyboard::S] || keys[sf::Keyboard::Down]) {
		movement = movement + Vector2f(0, -1);
	}
	if (keys[sf::Keyboard::A] || keys[sf::Keyboard::Left]) {
		movement = movement + Vector2f(-1, 0);
	}
	if (keys[sf::Keyboard::D] || keys[sf::Keyboard::Right]) {
		movement = movement + Vector2f(1, 0);
	}

	if (keys[sf::Keyboard::Num1] || keys[sf::Keyboard::Down]) {
		game->player.attack(0);
	}
	else {
		for (Weapon weapon : game->player.hands) {
			weapon.attacking = false;
		}
		game->player.hands[0].attacking = false;
	}

	game->player.move(movement.normalize(), dt);


	if (keys[sf::Keyboard::Y]) {
		keys[sf::Keyboard::Y] = false;
		NPC* n = findClosestNPC(game->player.position);

		if (n == 0);
		else if ((game->player.position^n->position) <= 10.0f) {
			n->trigger();
		}
	}

	if (keys[sf::Keyboard::J] && keys[sf::Keyboard::K]) {
		game->player.attack(0);
	}

	if (keys[sf::Keyboard::M]) {
		keys[sf::Keyboard::M] = false;
		game->player.position += -40.0f*(game->player.position2 - game->player.position1);
	}

	if (keys[sf::Keyboard::N]) {
		Screen::fadeWhite();
	}


	if (keys[sf::Keyboard::B]) {
		keys[sf::Keyboard::B] = false;
		testVar = !testVar;
		//Camera::setFocus(NPCManager::npcs["Rose"]);
	}

	if (keys[sf::Keyboard::LBracket]) {
		keys[sf::Keyboard::LBracket] = false;
		(++tilePointer) %= 64;
	}

	if (keys[sf::Keyboard::RBracket]) {
		keys[sf::Keyboard::RBracket] = false;
		(--tilePointer) %= 64;
	}

	if (keys[sf::Keyboard::P]) {
		keys[sf::Keyboard::P] = false;
		WorldManager::getCurrentWorld()->terrain->setTile(game->player.position + game->player.scale / 2, tilePointer);
	}

	if (keys[sf::Keyboard::X]) {
		keys[sf::Keyboard::X] = false;
		WorldManager::getCurrentWorld()->terrain->deleteChunk(game->player.position + game->player.scale / 2);
	}

	if (keys[sf::Keyboard::Num9]) {
		keys[sf::Keyboard::Num9] = false;
		WorldManager::currentWorld->terrain->saveTerrain(WorldManager::currentWorld->name);
	}

	if (keys[sf::Keyboard::J]) {
		keys[sf::Keyboard::J] = false;
		game->player.useSkill(0);
	}
	if (keys[sf::Keyboard::K]) {
		keys[sf::Keyboard::K] = false;
		game->player.useSkill(1);
	}
	if (keys[sf::Keyboard::L]) {
		keys[sf::Keyboard::L] = false;
		game->player.useSkill(2);
	}
	if (keys[sf::Keyboard::SemiColon]) {
		keys[sf::Keyboard::SemiColon] = false;
		game->player.useSkill(3);
	}
	if (keys[sf::Keyboard::U]) {
		keys[sf::Keyboard::U] = false;
		game->player.useSkill(4);
	}
	//if (keys[sf::Keyboard::I]) {
	//	keys[sf::Keyboard::I] = false;
	//	game->player.useSkill(5);
	//}
	//if (keys[sf::Keyboard::O]) {
	//	keys[sf::Keyboard::O] = false;
	//	game->player.useSkill(6);
	//}
	//if (keys[sf::Keyboard::P]) {
	//	keys[sf::Keyboard::P] = false;
	//	game->player.useSkill(7);
	//}
	//testing
	if (keys[sf::Keyboard::Comma]) {
		keys[sf::Keyboard::Comma] = false;
		game->player.levelUpSkill(1);
	}

	if (keys[sf::Keyboard::I]) {
		keys[sf::Keyboard::I] = false;
		game->state = GameState::INVENTORY;
	}

	if (keys[sf::Keyboard::Period]) {
		Weapon weapon = Weapon(0, 0, 0, Vector2f(0, 0), 1, Echo_Tex);
		game->player.addToInventory(weapon);
	}
}

void Input::InventoryLogic()
{
	if (keys[sf::Keyboard::W] || keys[sf::Keyboard::Up]) {
		keys[sf::Keyboard::W] = false;
		game->player.inventory.MoveUp();
	}
	if (keys[sf::Keyboard::S] || keys[sf::Keyboard::Down]) {
		keys[sf::Keyboard::S] = false;
		game->player.inventory.MoveDown();
	}
	if (keys[sf::Keyboard::A] || keys[sf::Keyboard::Left]) {
		keys[sf::Keyboard::A] = false;
		game->player.inventory.MoveLeft();
	}
	if (keys[sf::Keyboard::D] || keys[sf::Keyboard::Right]) {
		keys[sf::Keyboard::D] = false;
		game->player.inventory.MoveRight();
	}
	if (keys[sf::Keyboard::I]) {
		keys[sf::Keyboard::I] = false;
		game->player.inventoryOpen = false;
		//int displaying = game->player.ToggleInventory();
		game->state = GameState::FREE;
	}
	if (keys[sf::Keyboard::E]) {
		game->player.inventory.Select();
	}
}

void Input::LockedLogic()
{
}


Input::Input()
{
}


Input::~Input()
{
}
