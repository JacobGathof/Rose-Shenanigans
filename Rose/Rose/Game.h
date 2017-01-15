#pragma once
#include "Player.h"
#include "Building.h"
#include "World.h"
#include "WorldManager.h"
#include "ParticleSystem.h"
#include "LoadZone.h"
#include "Text.h"
#include "Terrain.h"
#include "NPC.h"
#include "Mission.h"
#include "UI_Element.h"


enum GameState {
	MENU,
	PAUSED,
	CLOSING,
	INVENTORY,
	FREE,
	LOCKED
};

class Game
{
public:
	Game() {};
	~Game() {};

	void tick();
	void init();
	void loop(float dt);
	void render();


	void renderMenu();
	void renderInventory();
	void renderFree();
	void renderPaused();

	void loopFree(float dt);
	void loopMenu();
	void loopInventory();
	void loopPaused();


	bool gameTick;
	float gameTime;
	int numberOfTicks;
	Player player;
	GameState state;

};

