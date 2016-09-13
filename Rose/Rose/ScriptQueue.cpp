#include "ScriptQueue.h"



ScriptQueue::ScriptQueue(Player *p, Entity *n)
{
	player = p;
	npc = n;

	scripts.push(Script(p, n));
}


ScriptQueue::~ScriptQueue()
{
}

void ScriptQueue::checkScript(){

	if (scripts.empty()) return;

	if (scripts.front().condition()) {
		scripts.front().action();
		scripts.pop();
	}

}
