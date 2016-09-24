#include "Input.h"
#include "Textbox.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;
int Input::tilePointer;

void Input::processInput(float dt)
{

	if (!Textbox::isVisible) {
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
			game->wizard.attack(0);
		}
		game->wizard.move(movement.normalize(), dt);


		if (keys[GLFW_KEY_Y]) {
			keys[GLFW_KEY_Y] = false;
			game->gary.interact();
			game->wizard.talkTo(game->gary);
		}
	}


	if (keys[GLFW_KEY_T]) {
		keys[GLFW_KEY_T] = false;
		if (!Textbox::currentlyWriting) {
			Textbox::advanceQueue();
		}
	}


	if (keys[GLFW_KEY_9]) {
		keys[GLFW_KEY_9] = false;
		WorldManager::currentWorld->terrain[0]->saveTerrain(WorldManager::currentWorld->name);
	}
	if (keys[GLFW_KEY_2]) {
		keys[GLFW_KEY_2] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->wizard.position, 1);
	}
	if (keys[GLFW_KEY_3]) {
		keys[GLFW_KEY_3] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->wizard.position, 2);
	}
	if (keys[GLFW_KEY_4]) {
		keys[GLFW_KEY_4] = false;
		WorldManager::currentWorld->terrain[0]->setTile(game->wizard.position, 4);
	}


}

Input::Input()
{
}


Input::~Input()
{
}
