#pragma once
#include <iostream>
#include <vector>


class Gem
{
public:
	Gem();
	~Gem();

	int durability;
	std::vector<int> attributes;

	void add(std::string attr, int level);
	int decode(std::string attr);
};

