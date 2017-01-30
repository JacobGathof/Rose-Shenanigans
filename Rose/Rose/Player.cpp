#include "Player.h"



Player::Player(Vector2f pos, Vector2f sc, std::string image, float speed)
	: Entity(pos, sc, image, speed)
{
	lastStep = pos;
	inventoryOpen = false;
	empty = Skill(0, 0, 0, 0, "empty_skill");
	for (int i = 0; i < 8; i++) {
		skills[i] = empty;
	}
	effectCounter = 0;
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
	for (int i = 0; i < 9; i++) {
		attributes[i] = 0;
	}
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
	//hands[hand].attack(NPC(), position, lastdirection);
}

void Player::equip(Weapon weapon, int hand)
{
	if (&hands[hand] != nullptr) {
		DeBuff(hands[hand]);
	}
	hands[hand] = weapon;
	ReBuff(hands[hand]);
}

void Player::addToInventory(Object item)
{
	//TODO
}

void Player::addToInventory(Weapon weapon)
{
	inventory.addWeapon(weapon);
}

int Player::ToggleInventory() {
	 return inventoryOpen = !inventoryOpen;
}

void Player::LevelUp()
{
	level++;
	maxXp += 20;
	exp = 0;
	stats = Text(Vector2f(40, -60), "Level: " + std::to_string(level), Vector2f(3, 3));
	statsChanged = true;
}

void Player::takeDamage(){

	if (iFrames > 0) {
		return;
	}
	this->hp -= 1;
	iFrames = 10;
	this->statsChanged = true;


}

void Player::addSkill(int index, Skill skill)
{
	skills[index] = skill;
}

void Player::useSkill(int index)
{
	int i = (&skills[index])->use(position, hands[0]);
	if (i == 1) {
		speed = 1200*(skills[index].level);
	}
}

void Player::levelUpSkill(int index)
{
	skills[index].level++;
}

void Player::StepBack(bool step)
{
	if (step) {
		position = lastStep;
	}
	else {
		lastStep = position;
	}
}

void Player::move(Vector2f dir, float dt) {
	if (!inventoryOpen) {
		Entity::move(dir, dt);
		CheckMissions();
		if (maxXp <= exp) {
			LevelUp();
		}
	}
}

void Player::draw() {
	if (hands[0].attacking) {
		hands[0].draw();
	}
	//for (int i = 0; i < 8; i++) {
	//	skills[i].draw(Vector2f(position.x - 70 + (10 * i), position.y-80));
	//}
	Entity::draw();
	//DisplayInventory(false);
}

void Player::tick(){
	if (!inventoryOpen) {
		Entity::tick();
		if (iFrames > 0)
			iFrames--;
		statusEffect();
	}
}

void Player::statusEffect()
{
	if (effectCounter % 20 == 0) {
		//takeDamage();
		this->hp -= attributes[0];
		this->hp -= attributes[1];
		this->hp -= attributes[4];
		this->hp -= attributes[5];
		this->statsChanged = true;
	}
	effectCounter++;
}

void Player::addStatus(int effect, int effectAmount)
{
	attributes[(int)std::log2(effect)] += effectAmount;
}

void Player::addGem(int hand, Gem gem, int index)
{
	DeBuff(hands[hand]);
	hands[hand].addGem(index, gem);
	ReBuff(hands[hand]);
}

void Player::removeGem(int hand, int index)
{
	DeBuff(hands[hand]);
	hands[hand].RemoveGem(index);
}

void Player::ReBuff(Weapon weapon)
{
	maxhp += weapon.attributes[(int)std::log2(ENVIGORATE)];
	maxmana += weapon.attributes[(int)std::log2(ENLIGHTENED)];
	bitmask = 0;
	for (int i = 0; i < 9; i++) {
		attributes[i] += weapon.attributes[i];
		if (attributes[i] != 0) {
			bitmask += pow(2, i);
		}
	}
}

void Player::DeBuff(Weapon weapon)
{
	maxhp -= weapon.attributes[ENVIGORATE];
	maxmana -= weapon.attributes[ENLIGHTENED];
	for (int i = 0; i < 9; i++) {
		attributes[i] -= weapon.attributes[i];
	}
}

