#include "Input.h"
#include "WorldManager.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;
int Input::tilePointer;
bool Input::isUsingJoystick = false;
int Input::joystick = 0;
int Input::lastFive[];

void Input::processInput(float dt)
{

	if (isUsingJoystick) {
		
		Vector2f movement;
		int count;
		const float * axes = glfwGetJoystickAxes(joystick, &count);

		float x = (abs(axes[0]) > .1f) ? axes[0] : 0;
		float y = (abs(axes[1]) > .1f) ? -axes[1] : 0;

		movement = Vector2f(x, y);
		game->player.move(movement*3, dt);


		const unsigned char* buttons = glfwGetJoystickButtons(joystick, &count);
		if (buttons[0] == GLFW_PRESS) {
			
		}
	}



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
	}
	

	if (keys[GLFW_KEY_J] && keys[GLFW_KEY_K]) {
		game->player.attack(0);
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
	
	if (lastFive[0] == 85 && lastFive[1] == 82 && lastFive[2] == 65 && lastFive[3] == 78 && lastFive[4] == 79) {
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

Input::Input()
{
}


Input::~Input()
{
}
