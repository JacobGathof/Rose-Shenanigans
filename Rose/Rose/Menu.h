#pragma once
#include "Text.h"
#include "Game.h"

class Menu
{
public:
	Menu();
	~Menu();

	static Text* menuItems[4];
	static int selectedIndex;
	static void setSelectedIndex(int i);
	static Game* game;

	static void actOnSelection();

	static void init(Game * ga);
	static void clean();
	static void render();
	static void update();

	//static Text *start, *exit, *settings, *credits;

};

