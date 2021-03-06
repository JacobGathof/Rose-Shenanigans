#pragma once
#include "WorldManager.h"
#include "ParticleSystem.h"
#include "LoadZone.h"
#include "Player.h"
#include "Terrain.h"
#include "Camera.h"
#include <vector>

class World
{
public:

	World();
	~World();
	World(std::string title);
	
	std::string name;
	std::vector<Object *> objects;
	std::vector<NPC *> npcs;
	std::vector<ParticleSystem *> systems;
	std::vector<Light *> lights;
	std::vector<LoadZone> zones;
	Terrain * terrain;
	
	void AddEntity(Entity * obj);
	void AddObject(Object * obj);
	void AddSystem(ParticleSystem * s);
	void AddLight(Light * l);
	void addTerrain(Terrain* t);
	void addNPC(NPC* n);

	NPC* findClosestNPC(Vector2f position);

	void tick();
	void update(float dt);
	void loadWorldResources();
	void AddLoadZone(LoadZone zone);
	World* checkLoad(Player* player);
	void draw();
	void unloadWorld();
	void checkEnemyCollisions(Player* player);
	void removeDead();
};

