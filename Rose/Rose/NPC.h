#pragma once
#include "Entity.h"
#include "Textbox.h"
#include <stack>

class NPC : public Entity
{
public:
	NPC(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	NPC();
	~NPC();

	bool isInteracting = false;

	void update(float dt);
	void addAction(std::string str);
	void print(std::string str);
	void interact();
	void act();
	int health;
};

