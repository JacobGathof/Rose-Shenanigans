#pragma once
#include <map>
#include "NPC.h"

class NPCManager
{
public:
	NPCManager();
	~NPCManager();

	static std::map<std::string, NPC*> npcs;
	static void init();
	static void destroy();
};

