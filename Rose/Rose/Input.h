#pragma once
#include "Game.h"
#include "opengl-wrapper\GLFW\include\GLFW\glfw3.h"

class Input
{
public:
	
	static bool keys[1024];
	static bool mouse[1024];
	static Game * game;

	static void processInput(float dt);

	Input();
	~Input();
};

