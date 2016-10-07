#include "Entity.h"
#include "WorldManager.h"
#include <iostream>


Entity::Entity(Vector2f pos, Vector2f scale, std::string texName, float speed)	: Object(pos, scale, texName)
{
	this->speed = speed;
	numberOfAnimationRows = 5;
	framesPerAnimation = 3;
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

	tex->bind();

	ShaderProgram * shader = Res::getShader(entityShader);
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);
	shader->loadFloat("animTimer", internalTime);
	shader->loadInteger("direction", direction);

	shader->loadInteger("rows", numberOfAnimationRows);
	shader->loadInteger("cols", framesPerAnimation);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

}

void Entity::update(float dt){

}

void Entity::tick(){

	internalTime += .05f;
	if (internalTime > framesPerAnimation)
		internalTime -= framesPerAnimation;
}
