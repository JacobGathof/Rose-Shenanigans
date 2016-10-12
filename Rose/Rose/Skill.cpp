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
	
}

void Skill::draw(Vector2f pos)
{
	//std::cout << name;
	//Object icon = Object(pos, Vector2f(20, 20), name);
	//icon.draw();
}

bool Skill::use(Vector2f pos, Weapon weapon)
{

	return false;
}
