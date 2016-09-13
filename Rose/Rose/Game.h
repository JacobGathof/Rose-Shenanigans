#pragma once
#include "Player.h"
#include "Building.h"
#include "World.h"
#include "WorldManager.h"
#include "LoadZone.h"
#include "Text.h"
#include "Terrain.h"
#include "NPC.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void tick();
	void init();
	void loop(float dt);
	void render();

	bool gameTick;
	float gameTime;
	Player wizard;
	Text text;

	NPC gary;
	
	Terrain terrain;
};

