#include "Gem.h"



Gem::Gem()
{
	durability = 100;
	for (int i = 0; i < 9; i++) {
		attributes[i] = 0;
	}
}

Gem::~Gem()
{
}

void Gem::add(double attr, int level)
{
	attributes[(int)std::log2(attr)] = level;
}

int Gem::decode(std::string attr)
{
	return 0;
}


