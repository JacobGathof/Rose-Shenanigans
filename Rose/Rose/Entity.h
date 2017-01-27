#pragma once
#include "Object.h"

enum Direction {
	SOUTH,
	EAST,
	WEST,
	NORTH,
};

enum State {
	MOVING,
	IDLE
};

class Entity :	public Object
{
public:

	float speed;
	float currentSpeed;

	virtual void move(Vector2f dir, float dt);
	virtual void draw();
	virtual void update(float dt);
	virtual void tick();
	virtual ObjectType getType() { return ENTITY; }

	Vector2f position1;
	Vector2f position2;

	Direction direction = SOUTH;
	State state = IDLE;
	bool continueAnimation = true;
	//Direction lastdirection = SOUTH;

	float internalTime = 0;

	Entity(Vector2f pos, Vector2f scale, TextureName texName, float speed = 1.0);
	Entity() {}
	~Entity() {};
};

