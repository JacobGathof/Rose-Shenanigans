#pragma once
#include "Entity.h"
#include <stack>
#include "ScriptQueue.h"

class NPC : public Entity
{
public:
	NPC(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	NPC();
	~NPC();

	void loadScripts(Player * player);

	ScriptQueue script;

	void update(float dt);
	void addAction(std::string str);
	void print(std::string str);
	void act();
	int health;
};

