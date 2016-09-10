#include "WorldManager.h"



WorldManager::WorldManager()
{
}


WorldManager::~WorldManager()
{
}

void WorldManager::addWorld(World area) {
	worlds.insert(std::pair<std::string, World>(area.name, area));
}

void WorldManager::swapWorld(std::string name) {
	world = worlds.at(name);
}
