#include "Input.h"
#include <iostream>

bool Input::keys[];
bool Input::mouse[];
Game* Input::game;

void Input::processInput(float dt)
{

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
		game->wizard.move(movement.normalize(), dt);


	if (mouse[GLFW_MOUSE_BUTTON_1]) {
		
	}
}

Input::Input()
{
}


Input::~Input()
{
}
