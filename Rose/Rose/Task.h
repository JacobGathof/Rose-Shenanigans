#pragma once
#include <queue>
#include "Vector2f.h"

class NPC;
class Task;

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

class TaskList {

public:

	TaskList();
	TaskList(Task* arr[]);
	std::vector<Task *> actions;
	int counter = 0;
	void advance();
	Task* getAction();
	void addAction(Task * action);
	bool isFinished();
	void reset();
	int nextIndex = 0;

};


class Task {

public:
	NPC * target;

	Task(ActionType type, std::string message) : type(type), message(message) {}
	Task(ActionType type) : type(type) {}
	Task(ActionType type, Vector2f endPoint) : type(type), endPoint(endPoint) {}
	Task(ActionType type, Vector2f * dir) : type(type), dir(dir) {}
	Task(ActionType type, void(*func)()) : type(type), function(func) {}

	bool finished = false;
	ActionType type;
	std::string message;
	Vector2f endPoint;
	Vector2f * dir;
	void(*function)();

	void act(float dt);

};

