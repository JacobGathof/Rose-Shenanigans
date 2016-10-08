#include "Slime.h"



Slime::Slime(Vector2f pos, Vector2f scale, std::string texName, float speed, Entity* target) : Entity(pos, scale, texName)
{
	this->speed = speed;
	this->target = target;
	numberOfAnimationRows = 1;
	framesPerAnimation = 8;
}


Slime::~Slime(){

}

void Slime::update(float dt){

	Entity::update(dt);
	follow(dt);

}

void Slime::tick(){

	Entity::tick();

}

void Slime::follow(float dt){

	Entity::move((target->position-position).normalize(), dt);

}
