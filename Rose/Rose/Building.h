#pragma once
#include "Vector2f.h"
#include "Object.h"
#include <iostream>
using namespace std;

class Building: public Object
{
public:
	Building();
	~Building();

	Building(Vector2f pos, string image, Vector2f sc, Vector2f doorPos);

	//WorldManager door;

};

