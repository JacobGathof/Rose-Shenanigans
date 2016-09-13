#include "WorldManager.h"


World WorldManager::currentWorld;
std::map<std::string, World> WorldManager::worlds;



void WorldManager::init(){


	World world = World("Town of Beginnings");
	world.AddEntity(new Entity(Vector2f(-30, 30), Vector2f(20, 20), "Edwin", 20));
	world.AddObject(new Building(Vector2f(.5, 0), "Inn", Vector2f(20, 20), Vector2f(.75, 0)));

	addWorld(world);

	//LoadZone zone = LoadZone("Second", 9, 9, Vector2f(55, 55));
	//world.AddLoadZone(zone);

	//world = World("Second");


	makeWorldCurrent("Town of Beginnings");

}

void WorldManager::addWorld(World area) {
	worlds[area.name] = area;
}

void WorldManager::loadWorld(World w)
{
}

World WorldManager::getWorld(std::string name)
{
	return worlds[name];
}

World WorldManager::getCurrentWorld()
{
	return currentWorld;
}

void WorldManager::makeWorldCurrent(std::string name)
{
	currentWorld = worlds[name];
}

void WorldManager::drawWorld(){

	currentWorld.draw();

}

void WorldManager::destroy(){
	for (auto w : worlds) {
		w.second.unloadWorld();
	}

}

void WorldManager::checkWorld(Player player) {
	std::string test = currentWorld.CheckLoad(player);
	if (!test.empty()) {
		currentWorld = worlds[test];
	}
}
