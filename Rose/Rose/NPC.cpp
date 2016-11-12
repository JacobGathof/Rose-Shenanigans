#include "NPC.h"
#include <iostream>
#include "WorldManager.h"


NPC::NPC(Vector2f pos, Vector2f scale, std::string texName, float speed) : Entity(pos, scale, texName, speed){
	name = "gary";
}

NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::update(float dt){

	if (!actionQueue.empty()) {
		NPCAction a = actionQueue.front();
		a.act(dt);
		if (a.finished) actionQueue.pop();
	}

	triggered = false;

}

void NPC::tick()
{
	Entity::tick();

	/*
	if (!actionQueue.empty() && actionQueue.front().finished) {
		actionQueue.pop();
	}
	*/
}


void NPC::trigger(){
	triggered = true;
}

bool NPC::print(std::string str){

	UIManager::textbox.print(str);
	return true;
}

bool NPC::moveTo(Vector2f endPoint, float dt)
{

	if (abs(position.x - endPoint.x) > 1.0f) {
		move(Vector2f(1 * (position.x - endPoint.x < 0.0 ? 1 : -1), 0), dt);
		return false;
	}

	else if(abs(position.y - endPoint.y) > 1.0f){
		move(Vector2f(0, 1 * (position.y - endPoint.y < 0.0 ? 1 : -1)), dt);
		return false;
	}

	return true;

}

bool NPC::idle(){
	return triggered;
}

bool NPC::detectPlayer()
{
	return ((this->position^Res::player->position) <= 16.0f);
}

void NPC::interact(){
	print("We must save my family!");
}

void NPC::act(){

}

void NPC::addAction(NPCAction a, bool doWait){
	a.target = this;
	actionQueue.push(a);
	
	/*
	if (doWait == 0) {
		NPCAction waiter(WAIT);
		waiter.target = this;
		actionQueue.push(waiter);
	}
	*/

}


void NPCAction::act(float dt){
	if (!finished) {
		switch (type) {
			case TALK: finished = target->print(message); break;
			case WAIT: finished = target->idle(); break;
			case MOVE: finished = target->moveTo(endPoint, dt); break;
			case WAIT_FOR_TEXTBOX: finished = !UIManager::textbox.isVisible; break;
			case DETECT_PLAYER: finished = target->detectPlayer(); break;
		}

	}
	
}

Echo::Echo() : NPC(Vector2f(100, 100), Vector2f(32, 32), "Echo", 50)
{
	addAction(NPCAction(MOVE, Vector2f(0,0)));
	addAction(NPCAction(TALK, "Welcome to the Town of Beginnings. Here, you can begin your adventure"));
	addAction(NPCAction(TALK, "Follow me to the inn."));
	addAction(NPCAction(WAIT_FOR_TEXTBOX));
	addAction(NPCAction(MOVE, Vector2f(200, 50)));
	addAction(NPCAction(DETECT_PLAYER));
	addAction(NPCAction(TALK, "Here we are! why don't you step inside for a moment?"));





}
