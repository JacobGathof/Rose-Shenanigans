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
	level = 1;
	bracket = Object(Vector2f(0, 0), Vector2f(8, 8), "bracket");
	icon = Object(Vector2f(0, 0), Vector2f(8, 8), name.data());
}

void Skill::draw(Vector2f pos)
{
	icon.position = pos;
	bracket.position = pos;
	icon.draw();
	bracket.draw();
}

int Skill::use(Vector2f pos, Weapon weapon)
{
	std::cout << "there" << std::endl;
	return 0;
}


	Dash::Dash()
		:Skill(0,0,0,0,"dash")
	{
		
	}

	
	int Dash::use(Vector2f pos, Weapon wep)
	{
		std::cout << "here" << std::endl;
		return 1;
	}

	

