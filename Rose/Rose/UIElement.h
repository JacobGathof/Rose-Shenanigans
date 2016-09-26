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
	virtual void init();
	virtual void destroy();
	virtual void update();

	bool isVisible;
};

