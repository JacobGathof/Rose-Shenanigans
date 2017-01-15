#include "Entity.h"
#include "WorldManager.h"
#include <iostream>
#include "Renderer.h"


Entity::Entity(Vector2f pos, Vector2f scale, std::string texName, float speed)	: Object(pos, scale, texName)
{
	this->speed = speed;
	internalTime = (float)(rand()) / RAND_MAX;
}


void Entity::move(Vector2f dir, float dt)
{

	state = (dir.x == 0 && dir.y == 0) ? IDLE : MOVING;

	if (dir.y > .707) direction = NORTH;
	if (dir.y < -.707) direction = SOUTH;

	if (dir.x > .707) direction = WEST;
	if (dir.x < -.707) direction = EAST;

	currentSpeed = speed;

	position.x += dir.x*currentSpeed*dt;
	if (WorldManager::collide(*this)) {
		position.x -= dir.x*currentSpeed*dt;
	}

	position.y += dir.y*currentSpeed*dt;
	if (WorldManager::collide(*this)) {
		position.y -= dir.y*currentSpeed*dt;
	}

}

void Entity::draw() {
	Renderer::renderEntity(this);

}

void Entity::update(float dt){

}

void Entity::tick(){

	if (state == MOVING || continueAnimation) {
		continueAnimation = true;
		internalTime += .125f;
		if (internalTime > tex->numberOfColumns) {
			internalTime -= tex->numberOfColumns;
			continueAnimation = false;
		}
	}
}