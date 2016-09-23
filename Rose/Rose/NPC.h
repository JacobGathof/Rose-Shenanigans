#pragma once
#include "Entity.h"
#include "Textbox.h"
#include <stack>
#include <iostream>

class NPC : public Entity
{
public:
	
	class NPCAction {

	public :
		enum ActionType {
			TALK,
			MOVE,
			FIGHT,
			WAIT,
			MOVE_SPECIAL,
		};


	public:
		NPC * target;

		NPCAction(NPC * target, ActionType type, std::string message)	: target(target), type(type), message(message) {}
		NPCAction(NPC * target, ActionType type)						: target(target), type(type) {}
		NPCAction(NPC * target, ActionType type, Vector2f endPoint)		: target(target), type(type), endPoint(endPoint) {}
		NPCAction(NPC * target, ActionType type, Vector2f * dir) : target(target), type(type), dir(dir) {}

		bool finished = false;
		ActionType type;
		std::string message;
		Vector2f endPoint;
		Vector2f * dir;

		void act(float dt) {
			if (!finished) {
				switch (type) {
					case TALK: finished = target->print(message); break;
					case WAIT: finished = target->idle(); break;
					case MOVE: finished = target->moveTo(endPoint, dt); break;
					case MOVE_SPECIAL: target->move(*dir, dt); finished = target->idle(); break;
				}

			}
		}

	};


	NPC(Vector2f pos, Vector2f scale, std::string texName, float speed = 1.0);
	NPC();
	~NPC();

	bool isInteracting = false;
	bool triggered = false;
	std::string name;
	
	void update(float dt);

	void trigger();
	bool print(std::string str);
	bool moveTo(Vector2f endPoint, float dt);
	bool idle();

	void interact();
	void act();
	int health;


	std::queue<NPCAction> actionQueue;
	void addAction(NPCAction a);


};

