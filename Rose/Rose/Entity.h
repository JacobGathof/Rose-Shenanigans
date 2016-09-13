#pragma once
#include "Object.h"

enum Direction {
	SOUTH,
	EAST,
	WEST,
	NORTH,
	IDLE, 
};

class Entity :	public Object
{
public:

	virtual void move(Vector2f dir, float dt);
	virtual void draw();
	virtual void update(float dt);
	virtual void tick();

	Direction direction = SOUTH;
	float internalTime = 0;

	int numberOfAnimationRows;
	int framesPerAnimation;

	Entity(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	Entity() {}
	~Entity() {};
};

