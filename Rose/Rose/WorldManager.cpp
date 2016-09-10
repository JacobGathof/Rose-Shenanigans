#include "WorldManager.h"



WorldManager::WorldManager()
{
}


WorldManager::~WorldManager()
{
}

WorldManager::WorldManager(World area) {
	worlds.insert(std::pair<std::string, World>(area.name, area));
	world = area;
	std::cout << area.objects.size();
}

void WorldManager::addWorld(World area) {
	worlds.insert(std::pair<std::string, World>(area.name, area));
}

void WorldManager::checkWorld(Player player) {
	std::string test = world.CheckLoad(player);
	if (!test.empty()) {
		world = worlds.at(test);
	}
}
