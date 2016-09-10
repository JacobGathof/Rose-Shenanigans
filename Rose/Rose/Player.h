#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <vector>
#include <iostream>

enum TypesOfHands {
	right,
	left
};

class Player: public Entity
{
public:
	Player() {};
	~Player() {};
	Player(Vector2f pos, Vector2f sc, std::string image, int speed);

	int maxhp;
	int hp;
	int maxmana;
	int mana;
	int morality;
	Weapon hands[2];
	std::vector<Object> inventory;


	virtual void move(Vector2f dir, float dt);

	
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
	
};

