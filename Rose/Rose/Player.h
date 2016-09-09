#pragma once
#include "Object.h"
#include "Weapon.h"
#include <vector>
#include <iostream>

class Player: public Object
{
public:
	Player();
	~Player();
	Player(int health, int maxhealth, int mana, int maxmana, int morality, Vector2f pos);

	int maxhp;
	int hp;
	int maxmana;
	int mana;
	int morality;
	Weapon hands[2];
	std::vector<Object> inventory;

	enum right;
	enum left;
	
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
	
};

