#pragma once
#include <queue>
#include <string>
#include "Text.h"

class Textbox
{
public:

	//Textbox();
	//~Textbox();

	static Text * text;
	static bool isWriting;
	static bool isVisible;

	static std::queue<std::string> queue;

	static void draw();
	static void init();
	static void destroy();
	static void advanceQueue();
	static void update();
	static void print(std::string message);

};

