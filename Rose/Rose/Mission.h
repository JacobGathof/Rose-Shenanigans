#pragma once
#include "Weapon.h"
#include "NPC.h"
#include <iostream>
class Mission
{
public:
	Mission();
	~Mission();
	Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, Vector2f pos);
	Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, NPC npc);
	Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, Object obj, int num);

	Vector2f posToComplete;
	NPC VP;
	int money;
	int experience;
	std::vector<Weapon> weapons;
	std::string text;
	std::string type;
	int numToKill;
	Object monster;
	bool talkedTo;

	void Talk(NPC npc);
	void Kill(Object obj);
	bool checkComplete(Vector2f pos);
	std::vector<Weapon> getReward(int i);
	int getReward();
	int getExp();
};

