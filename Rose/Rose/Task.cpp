#include "Task.h"
#include "NPC.h"
#include "WorldManager.h"
#include "UI_Manager.h"

void Task::act(float dt) {
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

TaskList::TaskList(){
	addAction(0);
}

TaskList::TaskList(Task * arr[])
{
	int counter = 0;
	do{
		addAction(arr[counter]);
	} while (arr[counter++] != 0);
}

void TaskList::advance(){
	counter++;
}

Task * TaskList::getAction(){
	Task* next = actions[counter];
	return next;
}

void TaskList::addAction(Task* action){
	actions.push_back(action);
}

bool TaskList::isFinished(){

	return actions[counter] == 0;
}

void TaskList::reset(){
	counter = 0;
	for (auto a : actions) {
		a->finished = false;
	}
}
