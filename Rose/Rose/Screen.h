#pragma once
class Screen
{
public:

	static float black;
	static float white;
	static float currentMax;
	
	static bool fadingBlack;
	static bool fadingWhite;
	static bool returning;

	static void fadeWhite(float duration = 1.0f);
	static void fadeBlack(float duration = 1.0f);

	static void update(float dt);
	static void reset();
};

