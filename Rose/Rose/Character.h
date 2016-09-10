#pragma once
#include <vector>

class Character
{
public:

	char ID;
	int x, y, width, height, xoffset, yoffset, xadvance;

	Character(std::vector<int> data);
	Character() {};
	~Character() {};
};

