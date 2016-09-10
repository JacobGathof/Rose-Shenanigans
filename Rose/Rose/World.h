#pragma once
#include "Object.h"
#include "Vector2f.h"
#include "LoadZones.h"
#include "Player.h"
#include "WorldManager.h"
#include <vector>
class World
{
public:
	World();
	~World();
	World(std::string title);
	
	std::string name;
	std::vector<Object> objects;
	std::vector<LoadZones> loadzones;
	
	void AddLoadZone(LoadZones zone);
	void CheckLoad(Player player, WorldManager manager);
	void Draw();
};

