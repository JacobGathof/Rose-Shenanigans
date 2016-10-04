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
			NPC* n = findClosestNPC(game->player.position);

			if (n == 0);
			else if((game->player.position^n->position) <= 10.0f){
				n->trigger();
			}
		}
	}


	if (keys[GLFW_KEY_T]) {
		keys[GLFW_KEY_T] = false;
		if (!UIManager::textbox.currentlyWriting) {
			UIManager::textbox.advanceQueue();
		}
	}


	if (keys[GLFW_KEY_O]) {
		keys[GLFW_KEY_O] = false;
		tilePointer = (tilePointer + 1) % 64;
		Res::getShader(uiShader)->loadInteger("tile", tilePointer);
	}

	if (keys[GLFW_KEY_I]) {
		keys[GLFW_KEY_I] = false;
		tilePointer = (tilePointer - 1) % 64;
		Res::getShader(uiShader)->loadInteger("tile", tilePointer);
	}

	if (keys[GLFW_KEY_P]) {
		keys[GLFW_KEY_P] = false;
		WorldManager::getCurrentWorld()->terrain[0]->setTile(game->player.position + game->player.scale / 2, tilePointer);
	}

	if (keys[GLFW_KEY_X]) {
		keys[GLFW_KEY_X] = false;
		WorldManager::getCurrentWorld()->terrain[0]->deleteChunk(game->player.position + game->player.scale / 2);
	}


	if (keys[GLFW_KEY_9]) {
		keys[GLFW_KEY_9] = false;
		WorldManager::currentWorld->terrain[0]->saveTerrain(WorldManager::currentWorld->name);
	}

}

NPC* Input::findClosestNPC(Vector2f position){
	return WorldManager::currentWorld->findClosestNPC(position);
}

Input::Input()
{
}


Input::~Input()
{
}
