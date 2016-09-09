#pragma once
#include "GLFW\glfw3.h"


class Input
{
public:

	static bool keys[1024];
	static bool mouse[1024];

	static void processInput();

	Input();
	~Input();
};

