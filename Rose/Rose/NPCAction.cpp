#include "NPCAction.h"
#include "NPC.h"
#include "WorldManager.h"


void NPCAction::act(float dt) {
	if (!finished) {
		switch (type) {
		case TALK: finished = target->print(message); break;
		case WAIT: finished = target->idle(); break;
		case MOVE: finished = target->moveTo(endPoint, dt); break;
		case WAIT_FOR_TEXTBOX: finished = !UIManager::textbox.isVisible; break;
		case DETECT_PLAYER: finished = target->detectPlayer(); break;
		case LAMBDA: function();  finished = true; break;
		}
	}
}

void NPCActionList::advance()
{
	counter++;
}

NPCAction * NPCActionList::getAction()
{
	NPCAction* next = actions[counter];
	return next;
}

void NPCActionList::addAction(NPCAction* action)
{
	actions.push_back(action);
	max++;
}

bool NPCActionList::isEmpty()
{
	return counter >= max;
}

void NPCActionList::reset()
{
	counter = 0;
	for (auto a : actions) {
		a->finished = false;
	}
}
