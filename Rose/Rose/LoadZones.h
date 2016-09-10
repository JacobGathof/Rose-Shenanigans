#pragma once
#include <iostream>
#include "Vector2f.h"
class LoadZones
{
public:
	LoadZones();
	~LoadZones();

	LoadZones(std::string name, int h, int w, Vector2f pos);

	std::string world;
	int height, width;
	Vector2f position;

};

