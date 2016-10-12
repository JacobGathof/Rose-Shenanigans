#pragma once
#include "Entity.h"
#include <vector>
#include <iostream>
#include "Mission.h"
#include "Text.h"
#include "Skill.h"

enum TypesOfHands {
	right,
	left
};

class Player: public Entity
{
public:
	virtual ObjectType getType() { return PLAYER; }

	Player() {};
	~Player() {};
	Player(Vector2f pos, Vector2f sc, std::string image, float speed);

	int iFrames = 0;

	int posInVec;
	int maxhp;
	int hp;
	int maxmana;
	int mana;
	int morality;
	int exp;
	int maxXp;
	int level;
	Skill empty;
	Skill skills[6];
	Weapon hands[2];
	std::vector<Object> inventory;
	std::vector<Mission> missions;
	Text stats;
	bool statsChanged = false;

	virtual void move(Vector2f dir, float dt);
	virtual void draw();
	virtual void tick();


	void talkTo(NPC npc);
	void addMission(Mission mission);
	void CheckMissions();
	void attack(int hand);
	void equip(Weapon weapon, int hand);
	void addToInventory(Object item);
	void LevelUp();
	void takeDamage();
};

