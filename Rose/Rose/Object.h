#pragma once
#include "Vector2f.h"
#include "Texture.h"
#include "Res.h"

enum ObjectType {
	OBJECT,
	ENTITY,
	PLAYER,
};

class Object
{
public:

	Vector2f position;
	Vector2f scale;
	Texture * tex;

	bool collide(Object obj);
	virtual void draw();
	virtual void tick();
	virtual void update(float dt);
	virtual ObjectType getType() { return OBJECT; }

	static bool compare(Object * o, Object * o2);

	Object();
	Object(Vector2f pos, Vector2f scale, std::string texName);
	~Object();
};

