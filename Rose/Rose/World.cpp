#include "World.h"
#include <algorithm>


World::World(){}
World::~World(){}


World::World(std::string title)
{
	name = title;
}

void World::tick()
{
	for (auto o : objects) {
		o->tick();
	}
}

void World::update(float dt){

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update(dt);
	}

	for (auto s : systems) {
		s->update(dt);
	}

	std::sort(objects.begin(), objects.end(), Object::compare);
	
	removeDead();

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
	objects.push_back(e);
}

void World::AddSystem(ParticleSystem * s) {
	systems.push_back(s);
}

void World::AddLight(Light * l){
	lights.push_back(l);
}

void World::addTerrain(Terrain * t){
	terrain = t;
}

void World::addNPC(NPC * n){
	npcs.push_back(n);
	objects.push_back(n);
}

NPC * World::findClosestNPC(Vector2f position)
{
	int min = -1;
	int minDist = 100;
	for (int i = 0; i < npcs.size(); i++) {
		float dist = position^npcs[i]->position;
		if (dist < minDist) {
			min = i;
			minDist = dist;
		}
	}
	return (min == -1) ? 0 : npcs[min];
}


void World::draw() {

	terrain->draw();

	for (auto o : objects) {
		if (o->getType() == PROJECTILE) {
		}
		if (((o->position.x + o->scale.x) > (Camera::position.x - SCALEFACTOR)) && (o->position.x < (Camera::position.x + SCALEFACTOR)) &&
			((o->position.y + o->scale.y) > (Camera::position.y - SCALEFACTOR)) && (o->position.y < (Camera::position.y + SCALEFACTOR))) {
			o->draw();
		}
	}

	//for (auto e : entities) {
		//e->draw();
	//}

	for (auto s : systems) {
		if (s->isActive()) {
			s->draw();
		}
	}

	for (auto l : zones) {
		l.draw();
	}

}

void World::unloadWorld(){

	for (auto o : objects) {
		if(o->getType() != PLAYER && o->getType() != NPC_)
			delete o;
	}

	for (auto e : systems) {
		delete e;
	}

	for (auto e : lights) {
		delete e;
	}
	delete terrain;
}

void World::checkEnemyCollisions(Player * player){
	for (auto o : objects) {
		if (o->getType() == SLIME) {
			if (o->collide(*player)) {
				player->takeDamage();
				if (player->attributes[0] == 0)
					player->addStatus(FIRE, 1);
				//o->destroy();
			}
		}
		if (o->getType() == PROJECTILE) {
			if (o->collide(*player)) {
				player->takeDamage();
				o->destroy();
			}
		}
	}
}

void World::removeDead()
{
	for (int i = 0; i < objects.size(); i++) {
		Object * obj = objects[i];
		if ((obj->getType() == SLIME || obj->getType() == PROJECTILE) && obj->alive == false) {
			delete obj;
			objects.erase(objects.begin() + i);
			i--;
		}
	}

}

World * World::checkLoad(Player* player) {

	for (auto z : zones) {
		if (z.position.y <= player->position.y + player->scale.y && z.position.y + z.scale.y >= player->position.y) {
			if (z.position.x <= player->position.x + player->scale.x && z.position.x + z.scale.x >= player->position.x) {
				if (z.movePlayer) {
					player->position = z.targetPosition;
				}
				return z.targetWorld;
			}
		}
	}
	return 0;

}