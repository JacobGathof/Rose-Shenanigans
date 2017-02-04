#pragma once
#include "opengl-wrapper\SFML\include\SFML\System\Clock.hpp"

class Timer
{
public:

	static float dt;
	static float gameTime;
	static bool tick;
	static bool slow;

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
	static sf::Clock clock;


	Timer() {};
	~Timer() {};
};

