#pragma once
#include <iostream>
#include "Vector2f.h"

class World;

class LoadZone
{
public:
	LoadZone();
	~LoadZone();

	LoadZone(World * currentWorld, World * targetWorld, Vector2f position, Vector2f scale);
	
	World* currentWorld;
	World* targetWorld;

	Vector2f scale;
	Vector2f position;

	void draw();

};

