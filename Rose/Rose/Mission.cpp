#include "Mission.h"



Mission::Mission()
{
}


Mission::~Mission()
{
}

Mission::Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, Vector2f pos)
{
	money = $$;
	experience = exp;
	for (int i = 0; i < wep.size(); i++) {
		weapons.push_back(wep.at(i));
	}
	text = tex;
	posToComplete = pos;
	type = "position";
}


Mission::Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, NPC npc)
{
	money = $$;
	experience = exp;
	for (int i = 0; i < wep.size(); i++) {
		weapons.push_back(wep.at(i));
	}
	talkedTo = false;
	text = tex;
	VP = npc;
	type = "talk";
}

Mission::Mission(int $$, int exp, std::vector<Weapon> wep, std::string tex, Object obj, int num)
{
	money = $$;
	experience = exp;
	for (int i = 0; i < wep.size(); i++) {
		weapons.push_back(wep.at(i));
	}
	text = tex;
	monster = obj;
	numToKill = num;
	type = "kill";
}

void Mission::Talk(NPC npc)
{
	if (npc.name == VP.name) {
		talkedTo = true;
	}
}

void Mission::Kill(Object obj)
{
	//this wont work
	if (obj.tex == monster.tex) {
		numToKill--;
	}
}

bool Mission::checkComplete(Vector2f pos)
{

	if (type == "kill") {
		return numToKill == 0;
	}
	else if (type == "talk") {
		return talkedTo;
	}
	else if (type == "position") {
		return (pos.x < posToComplete.x + 10 && pos.x > posToComplete.x - 10 && pos.y < posToComplete.y + 10 && pos.y > posToComplete.y - 10);
	}
}

std::vector<Weapon> Mission::getReward(int i)
{
	return weapons;
}

int Mission::getReward()
{
	return money;
}

int Mission::getExp()
{
	return experience;
}
