#include "Input.h"
#include "WorldManager.h"
#include <iostream>
#include "Screen.h"

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;
int Input::tilePointer;
bool Input::isUsingJoystick = false;
int Input::joystick = 0;
int Input::lastFive[];
bool Input::testVar = false;
bool Input::inInventory = false;


void Input::processInput(float dt)
{



	if (!UIManager::textbox.isVisible && !inInventory) {
		Vector2f movement;
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
			movement = movement + Vector2f(0, 1);
		}
		if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
			movement = movement + Vector2f(0, -1);
		}
		if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
			movement = movement + Vector2f(-1, 0);
		}
		if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
			movement = movement + Vector2f(1, 0);
		}

		if (keys[GLFW_KEY_1] || keys[GLFW_KEY_DOWN]) {
			game->player.attack(0);
		}
		else {
			for (Weapon weapon : game->player.hands) {
				weapon.attacking = false;
			}
			game->player.hands[0].attacking = false;
		}

		game->player.move(movement.normalize(), dt);


		if (keys[GLFW_KEY_Y]) {
			keys[GLFW_KEY_Y] = false;
			NPC* n = findClosestNPC(game->player.position);

			if (n == 0);
			else if ((game->player.position^n->position) <= 10.0f) {
				n->trigger();
			}
		}

		if (keys[GLFW_KEY_J] && keys[GLFW_KEY_K]) {
			game->player.attack(0);
		}

		if (keys[GLFW_KEY_M]) {
			Screen::fadeBlack();
		}
		if (keys[GLFW_KEY_N]) {
			Screen::fadeWhite();
		}


		if (keys[GLFW_KEY_B]) {
			keys[GLFW_KEY_B] = false;
			testVar = !testVar;
		}

		if (keys[GLFW_KEY_P]) {
			keys[GLFW_KEY_P] = false;
			WorldManager::getCurrentWorld()->terrain->setTile(game->player.position + game->player.scale / 2, tilePointer);
		}

		if (keys[GLFW_KEY_X]) {
			keys[GLFW_KEY_X] = false;
			WorldManager::getCurrentWorld()->terrain->deleteChunk(game->player.position + game->player.scale / 2);
		}

		if (keys[GLFW_KEY_9]) {
			keys[GLFW_KEY_9] = false;
			WorldManager::currentWorld->terrain->saveTerrain(WorldManager::currentWorld->name);
		}

		if (keys[GLFW_KEY_J]) {
			keys[GLFW_KEY_J] = false;
			game->player.useSkill(0);
		}
		if (keys[GLFW_KEY_K]) {
			keys[GLFW_KEY_K] = false;
			game->player.useSkill(1);
		}
		if (keys[GLFW_KEY_L]) {
			keys[GLFW_KEY_L] = false;
			game->player.useSkill(2);
		}
		if (keys[GLFW_KEY_SEMICOLON]) {
			keys[GLFW_KEY_SEMICOLON] = false;
			game->player.useSkill(3);
		}
		if (keys[GLFW_KEY_U]) {
			keys[GLFW_KEY_U] = false;
			game->player.useSkill(4);
		}
		//if (keys[GLFW_KEY_I]) {
		//	keys[GLFW_KEY_I] = false;
		//	game->player.useSkill(5);
		//}
		//if (keys[GLFW_KEY_O]) {
		//	keys[GLFW_KEY_O] = false;
		//	game->player.useSkill(6);
		//}
		//if (keys[GLFW_KEY_P]) {
		//	keys[GLFW_KEY_P] = false;
		//	game->player.useSkill(7);
		//}
		//testing
		if (keys[GLFW_KEY_COMMA]) {
			keys[GLFW_KEY_COMMA] = false;
			game->player.levelUpSkill(1);
		}

		if (keys[GLFW_KEY_I]) {
			keys[GLFW_KEY_I] = false;
			int displaying = game->player.ToggleInventory();
			inInventory = true;
			WorldManager::freeze = false;
			if (displaying) {
				WorldManager::freeze = true;
			}
		}

		if (keys[GLFW_KEY_PERIOD]) {
			Weapon weapon = Weapon(0, 0, 0, Vector2f(0, 0), 1, "Echo");
			game->player.addToInventory(weapon);
		}
	}
	
	if (inInventory) {
		InventoryKeys();
	}
	
	if (keys[GLFW_KEY_T]) {
		keys[GLFW_KEY_T] = false;
		if (!UIManager::textbox.currentlyWriting) {
			UIManager::textbox.advanceQueue();
		}
	}


	if (lastFive[0] == 83 && lastFive[1] == 65 && lastFive[2] == 78 && lastFive[3] == 73 && lastFive[4] == 67) {
		game->player.speed *= 2;
		lastFive[0] = 0;
	}

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


void Input::InventoryKeys()
{
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		keys[GLFW_KEY_W] = false;
		game->player.inventory.MoveUp();
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		keys[GLFW_KEY_S] = false;
		game->player.inventory.MoveDown();
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		keys[GLFW_KEY_A] = false;
		game->player.inventory.MoveLeft();
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		keys[GLFW_KEY_D] = false;
		game->player.inventory.MoveRight();
	}
	if (keys[GLFW_KEY_I]) {
		keys[GLFW_KEY_I] = false;
		int displaying = game->player.ToggleInventory();
		inInventory = false;
		WorldManager::freeze = false;
		if (displaying) {
			WorldManager::freeze = true;
		}
	}
	if (keys[GLFW_KEY_E]) {
		game->player.inventory.Select();
	}
}

Input::Input()
{
}


Input::~Input()
{
}
