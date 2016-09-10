#pragma once
#include "Player.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void init();
	void loop();
	void render();

	Player wizard;
};

