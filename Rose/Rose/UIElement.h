#pragma once
#include "Vector2f.h"
#include "Res.h"
#include <queue>
#include "Player.h"

class UIElement
{
public:
	UIElement();
	~UIElement();

	Vector2f topLeft;
	Vector2f botRight;

	Texture * tex;

	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

	bool isVisible;
};





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





class Textbox : public UIElement
{
public:

	Text * text;
	bool isDisplayingText;
	bool currentlyWriting;
	bool locked;

	static std::queue<std::string> queue;

	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

	void lock();
	void unlock();

	void advanceQueue();
	void print(std::string message);
	std::string splitString(std::string str);
	int findIndex(std::string str, int start, int end);
};




class Skillbox : public UIElement 
{
public:
	Skillbox();

	virtual void init();
	virtual void draw(Player *player);
};




