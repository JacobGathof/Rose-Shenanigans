#include "Input.h"
#include "Textbox.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;

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
		}
	}


	if (keys[GLFW_KEY_T]) {
		keys[GLFW_KEY_T] = false;
		if (!Textbox::currentlyWriting) {
			Textbox::advanceQueue();
		}
	}


}

Input::Input()
{
}


Input::~Input()
{
}
