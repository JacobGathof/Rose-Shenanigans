#pragma once
#include "Vector2f.h"
#include "Res.h"

class UIElement
{
public:
	UIElement();
	~UIElement();

	Vector2f topLeft;
	Vector2f botRight;

	virtual void draw();
	bool isVisible;
};

