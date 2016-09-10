#pragma once
#include "Player.h"
#include "Building.h"
#include "World.h"
#include "WorldManager.h"
#include "LoadZones.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void init();
	void loop(float dt);
	void render();

	World world;
	WorldManager worldmg;
	float gameTime;
	Entity edwin;
	Player wizard;
	Building building;
	LoadZones zone;
	
};

