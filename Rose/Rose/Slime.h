#pragma once
#include "Entity.h"

class Slime : public Entity
{
public:
	Slime(Vector2f pos, Vector2f scale, std::string texName, float speed, Entity * target);
	~Slime();

	Entity * target;

	virtual void update(float dt);
	virtual void tick();
	virtual ObjectType getType() { return SLIME; }

	void follow(float dt);

};

