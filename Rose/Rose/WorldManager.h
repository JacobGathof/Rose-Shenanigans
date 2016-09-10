#pragma once
#include "World.h"
#include "Player.h"

#include <vector>
class WorldManager
{
public:
	WorldManager();
	~WorldManager();
	WorldManager(World area);

	World world;
	std::map<std::string, World> worlds;

	void addWorld(World area);
	void checkWorld(Player player);
};

