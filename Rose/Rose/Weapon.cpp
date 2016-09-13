#include "Weapon.h"
#include <time.h>


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

Weapon::Weapon(int dmg, int critdmg, int percent, Vector2f * pos, std::string texName) 
	: Entity(*pos + Vector2f(10,10), Vector2f(5, 5), texName, 0)
{
	texture = texName;
	critdamage = dmg;
	critpercent = percent;
	damage = dmg;
}

/*
bool Weapon::attack(NPC obj)
{
	draw();
	if (collide(obj)) {
		if (rand() % 100 <= critpercent) {
			obj.health -= critdamage;
		}
		else {
			obj.health -= damage;
		}
	}
	return false;
}
*/