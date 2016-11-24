#pragma once
#include <iostream>
#include <vector>
#include "Info.h"

class Gem
{
public:
	Gem();
	~Gem();

	int durability;
	int attributes[9];

	void add(double attr, int level);
	int decode(std::string attr);
};

