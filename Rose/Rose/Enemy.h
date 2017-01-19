#pragma once
#include "Entity.h"
#include "World.h"
#include "Projectile.h"

struct VectorAndTime {
	Vector2f v1;
	Vector2f v2;
	float d1;
	float d2;
	float time1;
	float time2;
};


class Enemy : public Entity
{
public:
	Enemy(Entity * target, World* world, Vector2f pos, Vector2f scale, std::string texName, float speed);
	~Enemy();
	Entity* target;
	World* world;

	float cooldown = 5.0f;
	float current_cooldown = cooldown;

	float predict_cooldown = 1.0f;
	float current_predict_cooldown = predict_cooldown;

	VectorAndTime prediction;


	virtual void update(float dt);
	virtual void tick();

	void analyze();
	void follow(float dt);
	void shoot(float dt);
	void shootPrediction(float dt);




};

