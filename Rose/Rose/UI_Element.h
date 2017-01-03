#pragma once
#include "Vector2f.h"
#include "Res.h"
#include <queue>
#include "Player.h"
#include "Renderer.h"

#define UIElement UI_Element

class UIElement
{
public:
	UIElement();
	~UIElement();

	Vector2f topLeft;
	Vector2f botRight;
	static Vector2f toScreenCoordinates(int x, int y);

	Texture * tex;

	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

	bool isVisible;
};









class Inventory_Screen : public UIElement
{
public:
	Inventory_Screen(Player *player);
	~Inventory_Screen();

	Player * player;

	virtual void init();
	virtual void draw();
};

