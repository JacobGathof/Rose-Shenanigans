#pragma once
#include "Weapon.h"
#include "NPC.h"
#include "Vector2f.h"
#include "Object.h"
enum type {
	RANGED,
	MELEE,
	Spell
};
class Skill
{
public:
	Skill();
	~Skill();
	Skill(int dmg, int rng, int typ, int spd, std::string def);

	int damage;
	int attackType;
	int range;
	int speed;
	std::string name;
	Object icon;

	void draw(Vector2f pos);
	bool use(Vector2f pos, Weapon weapon);
};


