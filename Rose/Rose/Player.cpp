#include "Player.h"



Player::Player(Vector2f pos, Vector2f sc, std::string image, float speed)
	: Entity(pos, sc, image, speed)
{
	maxhp = 100;
	hp = 100;
	mana = 100;
	maxmana = 100;
	morality = 50;
	exp = 0;
	maxXp = 50;
	level = 1;
	stats = Text(Vector2f(40, -60), "Level: " + std::to_string(level), Vector2f(3, 3));
	statsChanged = true;
}

void Player::talkTo(NPC npc)
{
	for (unsigned int i = 0; i < missions.size(); i++) {
		missions.at(i).Talk(npc);
	}
	CheckMissions();
}

void Player::addMission(Mission mission)
{
	missions.push_back(mission);
}

void Player::CheckMissions()
{
	for (unsigned int i = 0; i < missions.size(); i++) {
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

void Player::LevelUp()
{
	level++;
	maxXp += 20;
	exp = 0;
	stats = Text(Vector2f(40, -60), "Level: " + std::to_string(level), Vector2f(3, 3));
	statsChanged = true;
}

void Player::move(Vector2f dir, float dt) {
	Entity::move(dir, dt);
	CheckMissions();
	if (maxXp <= exp) {
		LevelUp();
	}
}

void Player::draw() {
	if (hands[0].attacking) {
		hands[0].draw();
	}
	Entity::draw();
}

