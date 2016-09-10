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

void World::Draw() {
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i).draw();
	}
}

std::string World::CheckLoad(Player player) {
	for (int i = 0; i < loadzones.size(); i++) {
		LoadZones zone = loadzones.at(i);
		if (zone.position.y <= player.position.y + player.scale.y || zone.position.y + zone.height >= player.position.y) {
			if (zone.position.x <= player.position.x + player.scale.x || zone.position.x + zone.width >= player.position.x) {
				return zone.world;
			}
		}
	}
	return "";
}