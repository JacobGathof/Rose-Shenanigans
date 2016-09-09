#include "Player.h"


Player::Player()
{
	maxhp = 100;
	hp = 100;
	mana = 100;
	maxmana = 100;
	morality = 50;
}


Player::~Player()
{
}

Player::Player(int health, int maxhealth, int magic, int maxmagic, int moral, Vector2f pos, Vector2f sc, std::string image, int speed)
{
	__super::Object(pos, sc, image, speed);
	maxhp = maxhealth;
	hp = health;
	mana = magic;
	maxmana = maxmagic;
	morality = moral;
}

void Player::equip(Weapon weapon, int hand)
{
	hands[hand] = weapon;
}

void Player::addToInventory(Object item)
{
	inventory.push_back(item);
}

