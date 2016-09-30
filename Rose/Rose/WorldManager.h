#pragma once
#include "World.h"
#include "Building.h"
#include <vector>

class WorldManager
{
public:

	static void init();
	static void addToAllWorlds(Entity * e);
	static void addWorld(World * w);
	static void loadWorld(World w);
	static World* getWorld(std::string name);
	static World* getCurrentWorld();
	static void makeWorldCurrent(std::string name);
	static void drawWorld();
	static void destroy();

	static World * currentWorld;
	static std::map<std::string, World*> worlds;

	static void checkWorld(Player* player);
	static void tick();
	static void update(float dt);

};

