#include "LoadZone.h"



LoadZone::LoadZone()
{
}


LoadZone::~LoadZone()
{
}

LoadZone::LoadZone(std::string name, int h, int w, Vector2f pos) {
	world = name;
	height = h;
	width = w;
	position = pos;
}
