#pragma once
#include "UI_Element.h"
#define Textbox UI_Textbox

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