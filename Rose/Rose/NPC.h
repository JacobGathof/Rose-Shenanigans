#pragma once
#include "Entity.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include "NPCAction.h"



class NPC : public Entity
{
public:

	virtual ObjectType getType() { return NPC_; }

	NPC(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	NPC();
	~NPC();

	std::string name;
	int health;
	
	void update(float dt);
	void tick();

	void trigger();
	bool print(std::string str);
	bool moveTo(Vector2f endPoint, float dt);
	bool idle();
	bool detectPlayer();
	void interact();
	void act();

	bool isInteracting = false;
	bool triggered = false;
	Graph actionGraph;
	NPCActionList currentActionList;
	void addActionListToGraph(NPCActionList l, bool (*condition)());
	


};


class Echo : public NPC
{
public:
	Echo();

};

class Jibril : public NPC
{
public:
	Jibril();
};

