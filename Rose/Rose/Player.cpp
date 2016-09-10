#include "Player.h"



Player::Player(Vector2f pos, Vector2f sc, std::string image, int speed)
	: Entity(pos, sc, image, speed)
{

	maxhp = 100;
	hp = 100;
	mana = 100;
	maxmana = 100;
	morality = 50;
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
}

