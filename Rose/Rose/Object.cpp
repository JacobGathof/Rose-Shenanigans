#include "Object.h"
#include "Renderer.h"


bool Object::collide(Object obj)
{
	Vector2f ohp = obj.hitbox.position;
	Vector2f ohs = obj.hitbox.scale;

	Vector2f hp = hitbox.position;
	Vector2f hs = hitbox.scale;

	if (ohp.x+obj.position.x <= hp.x+position.x + hs.x && ohp.x+obj.position.x + ohs.x >= hp.x+position.x) {
		if (ohp.y+obj.position.y <= hp.y+position.y + hs.y && ohp.y+obj.position.y + ohs.y >= hp.y+position.y) {
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
	this->centerOfMass = position + .5f*scale;
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
	this->centerOfMass = Vector2f(0, 0);
}


Object::Object(Vector2f pos, Vector2f scale, TextureName texName){
	this->tex = Res::getTexture(texName);
	this->position = Vector2f(pos);
	this->scale = Vector2f(scale);
	this->hitbox.position = Vector2f(0, 0);
	this->hitbox.scale = Vector2f(scale);
	this->centerOfMass = position + .5f*scale;
}

Object::~Object(){
}
