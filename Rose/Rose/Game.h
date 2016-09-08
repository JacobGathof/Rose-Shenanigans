#pragma once
#include "Object.h"

class Game
{
public:
	Game() {};
	~Game() {};

	void init();
	void loop();
	void render();

	Object wizard;
};

