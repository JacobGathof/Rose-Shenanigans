#pragma once
#include "Object.h"
#include "Weapon.h"
#include <vector>
#include <iostream>

enum TypesOfHands {
	right,
	left
};

enum Direction {
	SOUTH,
	EAST,
	WEST,
	NORTH
};

class Player: public Object
{
public:
	Player();
	~Player();
	Player(int health, int maxhealth, int mana, int maxmana, int morality, Vector2f pos, Vector2f sc, std::string image, int speed);

	int maxhp;
	int hp;
	int maxmana;
	int mana;
	int morality;
	Weapon hands[2];
	std::vector<Object> inventory;

	Direction direction = SOUTH;
	float internalTime = 0;
	virtual void move(Vector2f dir, float dt);

	
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
	
};

