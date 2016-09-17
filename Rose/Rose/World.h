#pragma once
#include "LightManager.h"
#include "ParticleSystem.h"
#include "LoadZone.h"
#include "Player.h"
#include "Terrain.h"
#include <vector>

class World
{
public:
	World();
	~World();
	World(std::string title);
	
	std::string name;
	std::vector<Object *> objects;
	std::vector<Entity *> entities;
	std::vector<ParticleSystem *> systems;
	std::vector<Light *> lights;
	std::vector<Terrain *> terrain;
	std::vector<LoadZone> zones;
	
	void AddEntity(Entity * obj);
	void AddObject(Object * obj);
	void AddSystem(ParticleSystem * s);
	void AddLight(Light * l);
	void addTerrain(Terrain* t);

	void tick();
	void update(float dt);
	void loadWorldResources();
	void AddLoadZone(LoadZone zone);
	World* checkLoad(Player* player);
	void draw();
	void unloadWorld();
};

