#pragma once
#include "World.h"

#include <vector>
class WorldManager
{
public:
	WorldManager();
	~WorldManager();

	World world;
	std::map<std::string, World> worlds;

	void addWorld(World area);
	void swapWorld(std::string name);
};

