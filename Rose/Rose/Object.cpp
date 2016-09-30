#include "Object.h"



bool Object::collide(Object obj)
{
	if (obj.position.x <= position.x + scale.x || obj.position.x + obj.scale.x >= position.x) {
		if (obj.position.y <= position.y + scale.y || obj.position.y + obj.scale.y>= position.y) {
			return true;
		}
	}
	return false;
}



void Object::draw(){
	tex->bind();
	
	ShaderProgram * shader = Res::getShader(staticShader);
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

}

void Object::tick()
{
}

void Object::update(float dt)
{
}

bool Object::compare(Object * o, Object * o2)
{
	return o->position.y > o2->position.y;
}

Object::Object(){
	this->tex = 0;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1,1);
}


Object::Object(Vector2f pos, Vector2f scale, std::string texName){
	this->tex = Res::getTexture(texName);
	this->position = Vector2f(pos);
	this->scale = Vector2f(scale);
}

Object::~Object()
{
}
