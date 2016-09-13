#pragma once
#include <queue>
#include "Script.h"
#include "Player.h"

class ScriptQueue
{
public:

	ScriptQueue() {};
	ScriptQueue(Player * p, Entity * n);
	~ScriptQueue();

	Player * player;
	Entity * npc;

	std::queue<Script> scripts;
	void checkScript();

};

