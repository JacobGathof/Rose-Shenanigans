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
	: Object(pos, sc, image, speed)
{

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

void Player::move(Vector2f dir, float dt) {

	if (dir.x == 0 && dir.y == 0) internalTime = 0;

	if (dir.x > .75) direction = WEST;
	if (dir.x < -.75) direction = EAST;

	if (dir.y > .75) direction = NORTH;
	if (dir.y < -.75) direction = SOUTH;


	position = position + dir*speed*dt;

	internalTime += dt;

}

