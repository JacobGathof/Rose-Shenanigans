#pragma once
#include <iostream>
#include "Vector2f.h"
class LoadZone
{
public:
	LoadZone();
	~LoadZone();

	LoadZone(std::string name, int h, int w, Vector2f pos);

	std::string world;
	int height, width;
	Vector2f position;

};

