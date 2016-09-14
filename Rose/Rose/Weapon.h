#pragma once
#include "Entity.h"
#include "Vector2f.h"
#include "NPC.h"
class Weapon : public Entity
{
public:
	Weapon();
	~Weapon();
	Weapon(int dmg, int critdmg, int percent, Vector2f pos, std::string texName);

	std::string texture;
	//Vector2f* playerpos;
	int damage;
	int critdamage;
	int critpercent;

	bool attack(NPC obj, Vector2f pos, int dir);
};

