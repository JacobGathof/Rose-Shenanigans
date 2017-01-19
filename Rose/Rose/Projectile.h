#pragma once
#include "Entity.h"
#include "ParticleSystem.h"

class Projectile : public Entity
{
public:
	Projectile(Vector2f pos, Vector2f scale, std::string texName, float speed, Vector2f dir);
	~Projectile();

	Vector2f dir;
	float life = 2.0f;
	virtual void update(float dt);
	virtual void draw();
	virtual ObjectType getType() { return PROJECTILE; }

	ParticleSystem* system;

};



