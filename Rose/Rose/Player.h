#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <vector>
#include <iostream>
#include "Mission.h"

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
	int exp;
	Weapon hands[2];
	std::vector<Object> inventory;
	std::vector<Mission> missions;

	virtual void move(Vector2f dir, float dt);

	void addMission(Mission mission);
	void CheckMissions();
	void attack(int hand);
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
};

