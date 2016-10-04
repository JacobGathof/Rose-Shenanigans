#include "NPC.h"
#include <iostream>
#include "UIManager.h"


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


void NPC::trigger(){
	triggered = true;
}

bool NPC::print(std::string str){

	UIManager::textbox.print(str);
	return true;
}

bool NPC::moveTo(Vector2f endPoint, float dt)
{
	Vector2f dir = endPoint - position;
	move(dir.normalize(), dt);

	if (dir.magnitude() < 0.5f) {
		position = endPoint;
		return true;
	}

	return false;
}

bool NPC::idle(){
	return triggered;
}

void NPC::interact(){
	print("We must save my family!");
}

void NPC::act(){

}

void NPC::addAction(NPCAction a){
	a.target = this;
	actionQueue.push(a);
}


void NPCAction::act(float dt){
	if (!finished) {
		switch (type) {
		case TALK: finished = target->print(message); break;
		case WAIT: finished = target->idle(); break;
		case MOVE: finished = target->moveTo(endPoint, dt); break;
		case MOVE_SPECIAL: target->move(*dir, dt); finished = target->idle(); break;
		}

	}
	
}
