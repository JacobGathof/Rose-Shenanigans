#pragma once
#include "UI_Element.h"
#include "UI_Textbox.h"
#include "UI_Skillbox.h"
#include "UI_Statbox.h"

#define UIManager UI_Manager

class UIManager {
public:

	static UIElement tilebox;
	static Textbox textbox;
	static Statbox statbox;
	static Skillbox skillbox;

	static void init();
	static void destroy();
	static void update();
	static void tick();
	static void drawTextured();

	UIManager();
	~UIManager();
};