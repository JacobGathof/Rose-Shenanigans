#pragma once
#include "UI_Element.h"
#define Skillbox UI_Skillbox


class Skillbox : public UIElement
{
public:
	Skillbox();

	virtual void init();
	virtual void draw(Player *player);
};
