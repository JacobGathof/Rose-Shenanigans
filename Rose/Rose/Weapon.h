#pragma once
#include "Entity.h"
#include "Vector2f.h"
#include "NPC.h"
#include "Gem.h"
class Weapon : public Entity
{
public:
	Weapon();
	~Weapon();
	Weapon(int dmg, int critdmg, int percent, Vector2f pos, int slotNum, std::string texName);

	std::string texture;
	//Vector2f* playerpos;
	int damage;
	int critdamage;
	int critpercent;
	std::vector<Gem> slots;
	int NumSlots;

	bool attacking = false;

	std::vector<int> GetBuffs();
	Gem addGem(int index, Gem gem);
	bool attack(NPC obj, Vector2f pos, int dir);
};

