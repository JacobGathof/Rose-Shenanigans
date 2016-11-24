#pragma once
#include <queue>
#include "Vector2f.h"

class NPC;
class NPCAction;

enum ActionType {
	TALK,
	MOVE,
	FIGHT,
	WAIT,
	WAIT_FOR_TEXTBOX,
	DETECT_PLAYER,
	MOVE_SPECIAL,
	LAMBDA,
};

class NPCActionList {

public:

	NPCActionList();
	NPCActionList(NPCAction* arr[]);
	std::vector<NPCAction *> actions;
	int counter = 0;
	int max = 0;
	void advance();
	NPCAction* getAction();
	void addAction(NPCAction * action);
	bool isEmpty();
	void reset();

};


class NPCAction {

public:
	NPC * target;

	NPCAction(ActionType type, std::string message) : type(type), message(message) {}
	NPCAction(ActionType type) : type(type) {}
	NPCAction(ActionType type, Vector2f endPoint) : type(type), endPoint(endPoint) {}
	NPCAction(ActionType type, Vector2f * dir) : type(type), dir(dir) {}
	NPCAction(ActionType type, void(*func)()) : type(type), function(func) {}

	bool finished = false;
	ActionType type;
	std::string message;
	Vector2f endPoint;
	Vector2f * dir;
	void(*function)();

	void act(float dt);

};

