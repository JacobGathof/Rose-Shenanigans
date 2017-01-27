#include "Slime.h"



Slime::Slime(Vector2f pos, Vector2f scale, TextureName texName, float speed, Entity* target) : Entity(pos, scale, texName)
{
	this->speed = speed;
	this->target = target;
}


Slime::~Slime(){

}

void Slime::update(float dt){

	Entity::update(dt);
	//follow(dt);

}

void Slime::tick(){

	Entity::tick();

}

void Slime::follow(float dt){

	Entity::move(((target->position+target->scale/2)-(position+scale/2)).normalize(), dt);

}
