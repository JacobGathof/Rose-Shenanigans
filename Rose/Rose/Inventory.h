#pragma once
#include <vector>
#include <iostream>
#include "Weapon.h"
#include "Object.h"
#include "Text.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	std::vector<Weapon> weapons;
	int page;
	bool initialized;
	Object BackDrop;
	Text tab1;
	Text tab2;
	Text tab3;

	int Display(int health, int mana, int xp, Vector2f pos);
	void addWeapon(Weapon weapon);
	void discard(Weapon weapon);

};

