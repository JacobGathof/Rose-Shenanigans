#include "Skill.h"

Skill::Skill()
{
}


Skill::~Skill()
{
}

Skill::Skill(int dmg, int rng, int typ, int spd, TextureName def)
{
	damage = dmg;
	range = rng;
	attackType = typ;
	speed = spd;
	name = def;
	level = 1;
	bracket = Object(Vector2f(0, 0), Vector2f(8, 8), Bracket);
	icon = Res::getTexture(def);
}

int Skill::use(Vector2f pos, Weapon weapon)
{
	std::cout << "there" << std::endl;
	return 0;
}


	Dash::Dash()
		:Skill(0,0,0,0,Dash_Tex)
	{
		
	}

	
	int Dash::use(Vector2f pos, Weapon wep)
	{
		std::cout << "here" << std::endl;
		return 1;
	}

	

