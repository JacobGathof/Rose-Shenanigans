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
