#include "World.h"



World::World()
{
}


World::~World()
{
}

World::World(std::string title)
{
	name = title;
}

void World::AddLoadZone(LoadZones zone) {
	
	loadzones.push_back(zone);
}

void World::AddObject(Object * obj) {
	objects.push_back(obj);
	std::cout << objects.size();
}

void World::AddEntity(Entity * obj) {
	entities.push_back(obj);
}

void World::Draw() {
	for (int i = 0; i < objects.size(); i++) {
		Object obj = *objects.at(i);
		(*objects.at(i)).draw();
	}
	for (int i = 0; i < entities.size(); i++) {
		(*entities.at(i)).draw();
	}
}

std::string World::CheckLoad(Player player) {
	for (int i = 0; i < loadzones.size(); i++) {
		LoadZones zone = loadzones.at(i);
		if (zone.position.y <= player.position.y + player.scale.y && zone.position.y + zone.height >= player.position.y) {
			std::cout << zone.position.y + zone.height << std::endl;
			std::cout << player.position.y << std::endl;
			if (zone.position.x <= player.position.x + player.scale.x && zone.position.x + zone.width >= player.position.x) {
				return zone.world;
			}
		}
	}
	return "";
}