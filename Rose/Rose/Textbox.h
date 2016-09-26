#pragma once
#include <queue>
#include <string>
#include "Text.h"
#include "Res.h"
#include "UIElement.h"

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

};

