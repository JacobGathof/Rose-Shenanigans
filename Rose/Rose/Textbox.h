#pragma once
#include <queue>
#include <string>
#include "Text.h"
#include "Res.h"
#include "UIElement.h"

class Textbox : public UIElement
{
public:

	//Textbox();
	//~Textbox();

	Text * text;
	bool isDisplayingText;
	bool currentlyWriting;
	bool isVisible;
	bool locked;

	//Vector2f topLeft;
	//Vector2f botRight;

	static std::queue<std::string> queue;

	virtual void draw();
	void init();
	void destroy();

	void lock();
	void unlock();
	void advanceQueue();
	void update();
	void print(std::string message);

};

