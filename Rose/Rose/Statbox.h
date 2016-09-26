#pragma once
#include "UIElement.h"
#include "Player.h"
#include "Text.h"

class Statbox : public UIElement
{
public:
	Player * player;
	Text * text;

	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

	Statbox();
	~Statbox();
};

