#pragma once
#include "Player.h"
#include "Building.h"
#include "World.h"
#include "WorldManager.h"
#include "LoadZone.h"
#include "Text.h"
#include "Terrain.h"

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
	LoadZone zone;
	Text text;
	
	Terrain terrain;
};

