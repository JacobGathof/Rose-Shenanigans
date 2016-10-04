#include "NPCManager.h"
#include "WorldManager.h"


std::map<std::string, NPC*> NPCManager::npcs;


NPCManager::NPCManager()
{
}


NPCManager::~NPCManager()
{
}

void NPCManager::init(){

	NPC* edwin = new NPC(Vector2f(10, 10), Vector2f(20, 20), "Edwin", 50);
	edwin->numberOfAnimationRows = 4;
	edwin->addAction(NPCAction(WAIT));
	edwin->addAction(NPCAction(MOVE, Vector2f(100,100)));
	edwin->addAction(NPCAction(WAIT));
	edwin->addAction(NPCAction(TALK, "It's dangerous to go alone/Take this"));


	NPC* george = new NPC(Vector2f(-30, -60), Vector2f(20, 20), "Rain", 50);
	george->numberOfAnimationRows = 5;
	george->addAction(NPCAction(WAIT));
	george->addAction(NPCAction(MOVE, Vector2f(-100, -100)));
	george->addAction(NPCAction(WAIT));
	george->addAction(NPCAction(MOVE, Vector2f(100, -100)));
	george->addAction(NPCAction(MOVE, Vector2f(0, 0)));
	george->addAction(NPCAction(WAIT));
	george->addAction(NPCAction(TALK, "Stop following me"));


	WorldManager::currentWorld->addNPC(edwin);
	WorldManager::currentWorld->addNPC(george);
}

void NPCManager::destroy()
{
	for (auto n : npcs) {
		delete n.second;
	}
}
