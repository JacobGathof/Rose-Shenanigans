#pragma once
#include "Entity.h"
#include <vector>
#include <iostream>
#include "Mission.h"
#include "Text.h"
#include "Skill.h"
#include "Inventory.h"

enum TypesOfHands {
	right,
	left
};

class Player: public Entity
{
public:
	virtual ObjectType getType() { return PLAYER; }
	
	Player() {};

	Player(Vector2f pos, Vector2f sc, std::string image, float speed);

	int iFrames = 0;

	bool inventoryOpen;
	int posInVec;
	int maxhp;
	int hp;
	int maxmana;
	int mana;
	int morality;
	int exp;
	int maxXp;
	int level;
	int bitmask;
	int cleanup = 0;
	//Skill *empty;
	Skill *skills[8];
	Weapon hands[2];
	int attributes[9];
	int effectCounter;
	Inventory inventory;
	std::vector<Mission> missions;
	Text stats;
	bool statsChanged = false;

	virtual void move(Vector2f dir, float dt);
	virtual void draw();
	virtual void tick();

	void statusEffect();
	void addStatus(int effect, int effectAmount);
	void addGem(int hand, Gem gem, int index);
	void removeGem(int hand, int index);
	void ReBuff(Weapon weapon);
	void DeBuff(Weapon weapon);
	void talkTo(NPC npc);
	void addMission(Mission mission);
	void CheckMissions();
	void attack(int hand);
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
	void addToInventory(Weapon weapon);
	int ToggleInventory();
	void LevelUp();
	void takeDamage();
	void addSkill(int index, Skill skill);
	void useSkill(int index);
	void levelUpSkill(int index);

	~Player() {
		//		skills.clear();
		if (skills) {
			std::cout << "here" << std::endl;
			for (auto a : skills) {
				//std::cout << i << std::endl;
				//std::cout << skills[i] << std::endl;
				delete a;
				std::cout << "here" << std::endl;
				//skills.at(i) = 0;
			}
		}
		//delete[] skills;
	};
};

