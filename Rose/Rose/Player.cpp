#include "Player.h"



Player::Player(Vector2f pos, Vector2f sc, std::string image, int speed)
	: Entity(pos, sc, image, speed)
{
	maxhp = 100;
	hp = 100;
	mana = 100;
	maxmana = 100;
	morality = 50;
	exp = 0;
}

void Player::addMission(Mission mission)
{
	missions.push_back(mission);
}

void Player::CheckMissions()
{
	for (int i = 0; i < missions.size(); i++) {
		if (missions.at(i).checkComplete(position)) {
			exp += missions.at(i).getExp();
			missions.at(i).getReward();
			missions.at(i).getReward(0);
			missions.erase(missions.begin() + i);
		}
	}
}

void Player::attack(int hand)
{

	hands[hand].attack(NPC(), position, lastdirection);
}

void Player::equip(Weapon weapon, int hand)
{
	hands[hand] = weapon;
}

void Player::addToInventory(Object item)
{
	inventory.push_back(item);
}

void Player::move(Vector2f dir, float dt) {
	Entity::move(dir, dt);
	CheckMissions();
}

