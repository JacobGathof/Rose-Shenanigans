#pragma once
#include "World.h"
#include "Player.h"
#include "Building.h"
#include "Entity.h"

#include <vector>
class WorldManager
{
public:


	static void init();
	static void addWorld(World w);
	static void loadWorld(World w);
	static World getWorld(std::string name);
	static World getCurrentWorld();
	static void makeWorldCurrent(std::string name);
	static void drawWorld();
	static void destroy();

	static World currentWorld;
	static std::map<std::string, World> worlds;

	static void checkWorld(Player player);
};

