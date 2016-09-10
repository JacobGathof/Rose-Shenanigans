#include "Character.h"
#include <iostream>


Character::Character(std::vector<int> data)
{

	ID = (char)data[0];
	x = data[1];
	y = data[2];
	width = data[3];
	height = data[4];
	xoffset = data[5];
	yoffset = data[6];
	xadvance = data[7];

}

