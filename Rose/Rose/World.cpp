#include "World.h"



World::World(){}
World::~World(){}



World::World(std::string title)
{
	name = title;
}

void World::AddLoadZone(LoadZone zone) {
	
	loadzones.push_back(zone);
}

void World::AddObject(Object * obj) {
	objects.push_back(obj);
}

void World::AddEntity(Entity * e) {
	entities.push_back(e);
}

void World::draw() {

	for (auto o : objects) {
		o->draw();
	}

	for (auto e : entities) {
		e->draw();
	}
}

void World::unloadWorld(){

	for (auto o : objects) {
		delete o;
	}

	for (auto e : entities) {
		delete e;
	}
}

std::string World::CheckLoad(Player player) {
	for (int i = 0; i < loadzones.size(); i++) {
		LoadZone zone = loadzones.at(i);
		if (zone.position.y <= player.position.y + player.scale.y && zone.position.y + zone.height >= player.position.y) {
			if (zone.position.x <= player.position.x + player.scale.x && zone.position.x + zone.width >= player.position.x) {
				return zone.world;
			}
		}
	}
	return "";
}