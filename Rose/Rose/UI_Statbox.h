#pragma once
#include "UI_Element.h"
#define Statbox UI_Statbox


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
