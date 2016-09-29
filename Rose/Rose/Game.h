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
#include "UIElement.h"

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
	Player player;

	NPC basicNPC;

	Vector2f circleVector;
};

