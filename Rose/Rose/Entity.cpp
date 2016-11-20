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
	if (dir.x == 0 && dir.y == 0) {
		direction = IDLE;
	}
	if (dir.y > .707) direction = NORTH;
	if (dir.y < -.707) direction = SOUTH;

	if (dir.x > .707) direction = WEST;
	if (dir.x < -.707) direction = EAST;
	if (direction != IDLE) {
		lastdirection = direction;
	}

	//position += dir*speed*dt;

	position.x += dir.x*speed*dt;
	if (WorldManager::collide(*this)) {
		position.x -= dir.x*speed*dt;
	}

	position.y += dir.y*speed*dt;
	if (WorldManager::collide(*this)) {
		position.y -= dir.y*speed*dt;
	}

}

void Entity::draw() {
	Renderer::renderEntity(this);

}

void Entity::update(float dt){

}

void Entity::tick(){

	internalTime += .10f;
	if (internalTime > tex->numberOfColumns)
		internalTime -= tex->numberOfColumns;
}