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

	Object bracket;
	int level;
	int damage;
	int attackType;
	int range;
	int speed;
	std::string name;
	Texture *icon;

	virtual int use(Vector2f pos, Weapon weapon);

};

class Dash : public Skill
{
public:
	Dash();
	int use(Vector2f pos, Weapon wep);
};


