#include "Object.h"



bool Object::collide(Object obj)
{
	if (obj.position.x <= position.x + scale.x || obj.position.x >= position.x) {
		if (obj.position.y <= position.y + scale.y || obj.position.y >= position.y) {
			return true;
		}
	}
	return false;
}

void Object::move()
{
}

void Object::draw(){
	tex->bind();
	
	ShaderProgram * shader = Res::getShader("simpleShader");
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

}

Object::Object(){
	//this->tex = Res::getTexture("Wizard");
	//this->position = Vector2f(0, 0);
	//this->scale = Vector2f(1,1);
	//this->speed = 1.0f;
}


Object::Object(Vector2f pos, Vector2f scale, std::string texName, float speed)
{
	this->tex = Res::getTexture(texName);
	this->position = Vector2f(pos.x, pos.y);
	this->scale = Vector2f(scale.x, scale.y);
	this->speed = speed;

}

Object::~Object()
{
}
