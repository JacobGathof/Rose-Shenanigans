#pragma once
#include "Object.h"
#include <vector>
class World
{
public:
	World();
	~World();
	World(std::string title);
	
	std::string name;
	std::vector<Object> objects;
	
	void Draw();
};

