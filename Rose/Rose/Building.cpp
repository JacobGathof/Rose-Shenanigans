#include "Building.h"



Building::Building()
{
}


Building::~Building()
{
}

Building::Building(Vector2f pos, string image, Vector2f sc, Vector2f doorpos) 
	: Object(pos, sc, image)
{
}