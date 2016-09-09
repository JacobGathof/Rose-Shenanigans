#include "Input.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;

void Input::processInput(float dt)
{
	if (keys[GLFW_KEY_W]) {
		game->wizard.move(dt*Vector2f(0, 1));
	}
	if (keys[GLFW_KEY_S]) {
		game->wizard.move(dt*Vector2f(0, -1));
	}
	if (keys[GLFW_KEY_A]) {
		game->wizard.move(dt*Vector2f(-1, 0));
	}
	if (keys[GLFW_KEY_D]) {
		game->wizard.move(dt*Vector2f(1, 0));
	}

	if (mouse[GLFW_MOUSE_BUTTON_1]) {
		
	}
}

Input::Input()
{
}


Input::~Input()
{
}
