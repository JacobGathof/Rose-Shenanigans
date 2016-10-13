#include "Skill.h"

Skill::Skill()
{
}


Skill::~Skill()
{
}

Skill::Skill(int dmg, int rng, int typ, int spd, std::string def)
{
	damage = dmg;
	range = rng;
	attackType = typ;
	speed = spd;
	name = def;
	icon = Object(Vector2f(0,0), Vector2f(20, 20), name.data());
}

void Skill::draw(Vector2f pos)
{
	icon.position = pos;
	//icon.draw();
}

bool Skill::use(Vector2f pos, Weapon weapon)
{

	return false;
}
