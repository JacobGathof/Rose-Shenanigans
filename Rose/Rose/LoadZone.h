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
	LoadZone(World * currentWorld, World * targetWorld, Vector2f targetPosition, Vector2f position, Vector2f scale);
	
	World* currentWorld;
	World* targetWorld;
	Vector2f targetPosition;

	bool movePlayer;

	Vector2f scale;
	Vector2f position;

	void draw();

};

