#pragma once
#include "Textbox.h"
class UIManager
{
public:

	static Textbox textbox;
	static void init();
	static void destroy();
	static void update();
	static void tick();

	UIManager();
	~UIManager();
};

