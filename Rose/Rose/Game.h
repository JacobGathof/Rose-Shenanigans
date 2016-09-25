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
	Player wizard;

	NPC gary;

	UIElement box;

	Vector2f circleVector;
};

