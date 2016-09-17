#include "World.h"



World::World(){}
World::~World(){}



World::World(std::string title)
{
	name = title;
}

void World::tick()
{
	for (auto e : entities) {
		e->tick();
	}
}

void World::update(float dt){

	for (auto s : systems) {
		s->update(dt);
	}

}

void World::loadWorldResources(){
	LightManager::clearLights();

	for (auto l : lights) {
		LightManager::addLight(l);
	}

}

void World::AddLoadZone(LoadZone zone) {
	
	zones.push_back(zone);
}

void World::AddObject(Object * obj) {
	objects.push_back(obj);
}

void World::AddEntity(Entity * e) {
	entities.push_back(e);
}

void World::AddSystem(ParticleSystem * s) {
	systems.push_back(s);
}

void World::AddLight(Light * l){
	lights.push_back(l);
}

void World::addTerrain(Terrain * t){
	terrain.push_back(t);
}


void World::draw() {

	for (auto o : objects) {
		o->draw();
	}

	for (auto e : entities) {
		e->draw();
	}

	for (auto s : systems) {
		s->draw();
	}

	for (auto t : terrain) {
		t->draw();
	}
}

void World::unloadWorld(){

	for (auto o : objects) {
		delete o;
	}
	for (auto e : entities) {
		delete e;
	}
	for (auto e : systems) {
		delete e;
	}
	for (auto e : lights) {
		delete e;
	}
	for (auto e : terrain) {
		delete e;
	}
}

World * World::checkLoad(Player* player) {

	for (auto z : zones) {
		if (z.position.y <= player->position.y + player->scale.y && z.position.y + z.scale.y >= player->position.y) {
			if (z.position.x <= player->position.x + player->scale.x && z.position.x + z.scale.x >= player->position.x) {
				return z.targetWorld;
			}
		}
	}
	return 0;

}