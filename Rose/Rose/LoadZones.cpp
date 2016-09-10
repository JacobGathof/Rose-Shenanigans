#include "LoadZones.h"



LoadZones::LoadZones()
{
}


LoadZones::~LoadZones()
{
}

LoadZones::LoadZones(std::string name, int h, int w, Vector2f pos) {
	world = name;
	height = h;
	width = w;
	position = pos;
}
