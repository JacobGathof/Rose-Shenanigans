#pragma once
#include "Player.h"
#include "Building.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void init();
	void loop(float dt);
	void render();

	float gameTime;
	Entity edwin;
	Player wizard;
	Building building;
};

