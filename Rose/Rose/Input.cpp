#include "Input.h"
#include "UIManager.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;
int Input::tilePointer;

void Input::processInput(float dt)
{

	if (!UIManager::textbox.isVisible) {
		Vector2f movement;
		if (keys[GLFW_KEY_W]) {
			movement = movement + Vector2f(0, 1);
		}
		if (keys[GLFW_KEY_S]) {
			movement = movement + Vector2f(0, -1);
		}
		if (keys[GLFW_KEY_A]) {
			movement = movement + Vector2f(-1, 0);
		}
		if (keys[GLFW_KEY_D]) {
			movement = movement + Vector2f(1, 0);
		}
		if (keys[GLFW_KEY_1]) {
			game->player.attack(0);
		}
		game->player.move(movement.normalize(), dt);


		if (keys[GLFW_KEY_Y]) {
			keys[GLFW_KEY_Y] = false;
			game->basicNPC.interact();
			game->player.talkTo(game->basicNPC);
		}
	}


	if (keys[GLFW_KEY_T]) {
		keys[GLFW_KEY_T] = false;
		if (!UIManager::textbox.currentlyWriting) {
			UIManager::textbox.advanceQueue();
		}
	}

	if (keys[GLFW_KEY_P]) {
		keys[GLFW_KEY_P] = false;
		WorldManager::getCurrentWorld()->terrain[0]->setTile(game->player.position, 1);
	}


	if (keys[GLFW_KEY_9]) {
		keys[GLFW_KEY_9] = false;
		WorldManager::currentWorld->terrain[0]->saveTerrain(WorldManager::currentWorld->name);
	}
	if (keys[GLFW_KEY_2]) {
		keys[GLFW_KEY_2] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->player.position, 1);
	}
	if (keys[GLFW_KEY_3]) {
		keys[GLFW_KEY_3] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->player.position, 2);
	}
	if (keys[GLFW_KEY_4]) {
		keys[GLFW_KEY_4] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->player.position, 4);
	}


}

Input::Input()
{
}


Input::~Input()
{
}
