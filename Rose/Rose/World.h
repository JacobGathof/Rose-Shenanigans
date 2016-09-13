#pragma once
#include "Object.h"
#include "Vector2f.h"
#include "LoadZone.h"
#include "Player.h"
#include "Entity.h"
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
	std::vector<LoadZone> loadzones;
	
	void AddEntity(Entity * obj);
	void AddObject(Object * obj);
	void AddLoadZone(LoadZone zone);
	std::string CheckLoad(Player player);
	void draw();
	void unloadWorld();
};

