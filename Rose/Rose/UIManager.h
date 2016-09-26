#pragma once
#include "Textbox.h"
#include "Statbox.h"

class UIManager
{
public:

	static Textbox textbox;
	static Statbox statbox;

	static void init();
	static void destroy();
	static void update();
	static void tick();

	UIManager();
	~UIManager();
};

