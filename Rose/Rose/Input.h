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

	static bool testVar;

	static void processInput(float dt);
	static void turnKeyOn(int key);
	static NPC* findClosestNPC(Vector2f position);


	static void MenuLogic();
	static void GameLogic(float dt);
	static void InventoryLogic();
	static void LockedLogic();

	Input();
	~Input();
};

