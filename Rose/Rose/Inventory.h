#pragma once
#include <vector>
#include <iostream>
#include "Weapon.h"
#include "Object.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	std::vector<Weapon> weapons;
	int page;
	Object BackDrop;

	int Display(int health, int mana, int xp, Vector2f pos);
	void addWeapon(Weapon weapon);
	void discard(Weapon weapon);

};

