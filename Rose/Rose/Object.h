#pragma once
#include "Vector2f.h"
#include "Texture.h"
#include "Res.h"

enum ObjectType {
	OBJECT,
	ENTITY,
	PLAYER,
	NPC_,
	SLIME,
	PROJECTILE,
	ENEMY

};

class Object
{
public:

	struct Hitbox {
		Vector2f position;
		Vector2f scale;
	};

	Hitbox hitbox;
	Vector2f position;
	Vector2f centerOfMass;
	Vector2f scale;
	Texture * tex;

	bool alive = true;

	bool collide(Object obj);
	virtual void draw();
	virtual void tick();
	virtual void update(float dt);
	virtual ObjectType getType() { return OBJECT; }
	virtual void destroy();

	static bool compare(Object * o, Object * o2);

	Object();
	Object(Vector2f pos, Vector2f scale, TextureName texName);
	~Object();
};

