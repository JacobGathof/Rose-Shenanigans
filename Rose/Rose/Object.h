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

};

class Object
{
public:

	struct Hitbox {
		Vector2f position;
		Vector2f scale;
	};

	int placeInList;
	Hitbox hitbox;
	Vector2f position;
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
	Object(Vector2f pos, Vector2f scale, std::string texName);
	~Object();
};

