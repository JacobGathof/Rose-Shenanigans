#pragma once
#include "Vector2f.h"
#include "Texture.h"
#include "Res.h"

class Object
{
public:

	Vector2f position;
	Vector2f scale;
	Texture * tex;
	float speed;

	bool collide(Object obj);
	virtual void draw();

	Object();
	Object(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	~Object();
};

