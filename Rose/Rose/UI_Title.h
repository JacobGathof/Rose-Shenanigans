#pragma once
#include "UI_Element.h"

#define Title UI_Title

class Title : public UIElement
{
public:

	Text * text;
	bool toDisplay = true;

	float currentIdle = 0.0f;
	bool rising = false;
	bool falling = false;
	int letterBuffer = 10;


	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

};

