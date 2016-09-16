#pragma once
#include <queue>
#include <string>
#include "Text.h"
#include "Res.h"

class Textbox
{
public:

	//Textbox();
	//~Textbox();

	static Text * text;
	static bool isDisplayingText;
	static bool currentlyWriting;
	static bool isVisible;
	static bool locked;

	static Vector2f topLeft;
	static Vector2f botRight;

	static std::queue<std::string> queue;

	static void draw();
	static void init();
	static void destroy();

	static void lock();
	static void unlock();
	static void advanceQueue();
	static void update();
	static void print(std::string message);

};

