#pragma once
#include "Game.h"
#include "opengl-wrapper\GLFW\include\GLFW\glfw3.h"

class Input
{
public:
	
	static bool keys[1024];
	static bool mouse[1024];
	static int lastFive[5];
	static Game * game;
	static int tilePointer;
	static bool isUsingJoystick;
	static int joystick;
	static bool inInventory;

	static bool testVar;

	static void InventoryKeys();
	static void processInput(float dt);
	static void turnKeyOn(int key);
	static NPC* findClosestNPC(Vector2f position);

	Input();
	~Input();
};

