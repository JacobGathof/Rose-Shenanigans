#pragma once
#include "opengl-wrapper\GLFW\include\GLFW\glfw3.h"

class Timer
{
public:

	static float dt;
	static float gameTime;
	static bool tick;

	static float currentTime;
	static float lastTime;
	static float lastSecond;
	static float lastTick;

	static int frameLimit;
	static int FPS;

	static void init() {};
	static void enableTick() {	tick = true;}
	static void disableTick() { tick = false; }

	static void wait();


	Timer() {};
	~Timer() {};
};

