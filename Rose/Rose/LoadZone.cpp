#include "LoadZone.h"


LoadZone::LoadZone()
{
}


LoadZone::~LoadZone()
{
}

LoadZone::LoadZone(World * currentWorld, World * targetWorld, Vector2f position, Vector2f scale){
	this->currentWorld = currentWorld;
	this->targetWorld = targetWorld;
	this->position = position;
	this->scale = scale;
}
