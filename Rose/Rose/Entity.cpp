#include "Entity.h"



Entity::Entity(Vector2f pos, Vector2f scale, std::string texName, float speed)
	: Object(pos, scale, texName, speed)
{
}


void Entity::move(Vector2f dir, float dt)
{
	if (dir.x == 0 && dir.y == 0) internalTime = 0;

	if (dir.x > .75) direction = WEST;
	if (dir.x < -.75) direction = EAST;

	if (dir.y > .75) direction = NORTH;
	if (dir.y < -.75) direction = SOUTH;


	position = position + dir*speed*dt;

	internalTime += dt;

}

void Entity::draw() {

	tex->bind();

	ShaderProgram * shader = Res::getShader("simpleShader");
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);
	shader->loadFloat("animTimer", internalTime);
	shader->loadInteger("direction", direction);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

}
