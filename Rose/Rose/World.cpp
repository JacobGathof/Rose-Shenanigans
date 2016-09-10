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



void World::Draw() {
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i).draw();
	}
}