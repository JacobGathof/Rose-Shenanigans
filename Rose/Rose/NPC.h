#pragma once
#include "Entity.h"
#include <queue>
#include <iostream>


enum ActionType {
	TALK,
	MOVE,
	FIGHT,
	WAIT,
	WAIT_FOR_TEXTBOX,
	DETECT_PLAYER,
	MOVE_SPECIAL,
};

class NPC;
class Player;

class NPCAction {

public:
	NPC * target;

	NPCAction(ActionType type, std::string message) : type(type), message(message) {}
	NPCAction(ActionType type) : type(type) {}
	NPCAction(ActionType type, Vector2f endPoint) : type(type), endPoint(endPoint) {}
	NPCAction(ActionType type, Vector2f * dir) : type(type), dir(dir) {}

	bool finished = false;
	ActionType type;
	std::string message;
	Vector2f endPoint;
	Vector2f * dir;

	void act(float dt);

};

class NPC : public Entity
{
public:

	virtual ObjectType getType() { return NPC_; }

	NPC(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	NPC();
	~NPC();

	bool isInteracting = false;
	bool triggered = false;
	std::string name;
	
	void update(float dt);
	void tick();

	void trigger();
	bool print(std::string str);
	bool moveTo(Vector2f endPoint, float dt);
	bool idle();
	bool detectPlayer();

	void interact();
	void act();
	int health;


	std::queue<NPCAction> actionQueue;
	void addAction(NPCAction a, bool doWait = 0);


};


class Echo : public NPC
{

public:
	Echo();


};

