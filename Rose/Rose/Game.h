#pragma once
#include "Player.h"
#include "Building.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void init();
	void loop();
	void render();

	Player wizard;
	Building building;
};

