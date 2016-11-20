#include "Object.h"
#include "Renderer.h"


bool Object::collide(Object obj)
{
	if (obj.hitbox.position.x <= hitbox.position.x + hitbox.scale.x && obj.hitbox.position.x + obj.hitbox.scale.x >= hitbox.position.x) {
		if (obj.hitbox.position.y <= hitbox.position.y + hitbox.scale.y && obj.hitbox.position.y + obj.hitbox.scale.y >= hitbox.position.y) {
			return true;
		}
	}
	return false;
}



void Object::draw(){
	Renderer::renderObject(this);
}


void Object::tick(){
}

void Object::update(float dt){
}

bool Object::compare(Object * o, Object * o2){
	return o->position.y > o2->position.y;
}


void Object::destroy() {
	alive = false;
}


Object::Object(){
	this->tex = 0;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1,1);
	this->hitbox.position = Vector2f(0, 0);
	this->hitbox.scale = scale;
}


Object::Object(Vector2f pos, Vector2f scale, std::string texName){
	this->tex = Res::getTexture(texName);
	this->position = Vector2f(pos);
	this->scale = Vector2f(scale);
	this->hitbox.position = Vector2f(0, 0);
	this->hitbox.scale = Vector2f(scale);
}

Object::~Object(){
}
