#include "Weapon.h"
#include <time.h>
#include <iostream>


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

Weapon::Weapon(int dmg, int critdmg, int percent, Vector2f pos, int slotNum, std::string texName) 
	: Entity(pos + Vector2f(15,20), Vector2f(20, 20), texName, 0)
{
	NumSlots = slotNum;
	texture = texName;
	critdamage = dmg;
	critpercent = percent;
	damage = dmg;
	for (int i = 0; i < 9; i++) {
		attributes[i] = 0;
	}
}

//std::vector<int> Weapon::GetBuffs()
//{
	//TODO
	//return std::vector<int>;
//}

Gem Weapon::addGem(int index, Gem gem)
{
	if (&(slots.at(index)) != NULL) {
		return slots.at(index);
	}
	slots.at(index) = gem;
	Reconfigure(index);
}

void Weapon::Reconfigure(int slot)
{
	attributes[(int)std::log2(FIRE)] += slots.at(slot).attributes[(int)std::log2(FIRE)];
	attributes[(int)std::log2(POISON)] += slots.at(slot).attributes[(int)std::log2(POISON)];
	attributes[(int)std::log2(SLOWED)] += slots.at(slot).attributes[(int)std::log2(SLOWED)];
	attributes[(int)std::log2(FROZEN)] += slots.at(slot).attributes[(int)std::log2(FROZEN)];
	attributes[(int)std::log2(CURSED)] += slots.at(slot).attributes[(int)std::log2(CURSED)];
	attributes[(int)std::log2(BLEEDING)] += slots.at(slot).attributes[(int)std::log2(BLEEDING)];
	attributes[(int)std::log2(STRENGTHEN)] += slots.at(slot).attributes[(int)std::log2(STRENGTHEN)];
	attributes[(int)std::log2(ENVIGORATE)] += slots.at(slot).attributes[(int)std::log2(ENVIGORATE)];
	attributes[(int)std::log2(ENLIGHTENED)] += slots.at(slot).attributes[(int)std::log2(ENLIGHTENED)];
}

Gem Weapon::RemoveGem(int slot)
{
	if (&slots.at(slot) == nullptr) {
		Gem gem;
		return gem;
	}
	SubtractBuffs(slots.at(slot));
	slots.at(slot).durability -= 10;
	//slots.erase(slots.begin + slot); // Check this for correct indexing
}

void Weapon::SubtractBuffs(Gem gem)
{
	attributes[(int)std::log2(FIRE)] -= gem.attributes[(int)std::log2(FIRE)];
	attributes[(int)std::log2(POISON)] -= gem.attributes[(int)std::log2(POISON)];
	attributes[(int)std::log2(SLOWED)] -= gem.attributes[(int)std::log2(SLOWED)];
	attributes[(int)std::log2(FROZEN)] -= gem.attributes[(int)std::log2(FROZEN)];
	attributes[(int)std::log2(CURSED)] -= gem.attributes[(int)std::log2(CURSED)];
	attributes[(int)std::log2(BLEEDING)] -= gem.attributes[(int)std::log2(BLEEDING)];
	attributes[(int)std::log2(STRENGTHEN)] -= gem.attributes[(int)std::log2(STRENGTHEN)];
	attributes[(int)std::log2(ENVIGORATE)] -= gem.attributes[(int)std::log2(ENVIGORATE)];
	attributes[(int)std::log2(ENLIGHTENED)] -= gem.attributes[(int)std::log2(ENLIGHTENED)];
}

bool Weapon::attack(NPC obj, Vector2f pos, int dir)
{
	position.x += (pos.x + 0) - position.x;
	position.y += (pos.y + 5) - position.y;
	if (dir == 0) {
		position.y -= 15;
	}
	if (dir == 1) {
		position.x -= 10;
	}
	else if (dir == 2) {
		position.x += 10;
	}
	if (dir == 0) {
		direction = SOUTH;
	}
	else if (dir == 1) {
		direction = EAST;
	}
	else if (dir == 2) {
		direction = WEST;
	}
	else {
		direction = NORTH;
	}
	attacking = true;
	/*
	if (collide(obj)) {
		if (rand() % 100 <= critpercent) {
			obj.health -= critdamage;
		}
		else {
			obj.health -= damage;
		}
	}
	*/
	return true;
}
