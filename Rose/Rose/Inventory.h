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

	Text page1[100];
	Text page2[100];
	Text page3[100];

	std::vector<Weapon> weapons;
	int page;
	int textSize = 3;
	bool initialized;
	Object BackDrop;
	Text tab1;
	Text tab2;
	Text tab3;

	void BuildPages();
	int Display(int health, int mana, int xp, Vector2f pos);
	void addWeapon(Weapon weapon);
	void discard(Weapon weapon);
};

