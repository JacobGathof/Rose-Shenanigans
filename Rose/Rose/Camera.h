#pragma once
#include "Vector2f.h"
#include "Object.h"

class Camera
{
public:
	static float speed;
	static Object * focus;
	static Vector2f position;
	static void setFocus(Object * object);
	static void setSpeed(float sp);
	static void update(float dt);
	Camera();
	~Camera();
};

