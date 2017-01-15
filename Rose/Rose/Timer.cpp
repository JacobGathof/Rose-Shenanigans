#include "Timer.h"


float Timer::dt = 0;
float Timer::gameTime = 0;
float Timer::currentTime = 0;
float Timer::lastTime = 0;
float Timer::lastTick = 0;
float Timer::lastSecond = 0;
int Timer::frameLimit = 120;
int Timer::FPS;
bool Timer::tick = false;

void Timer::wait(){

	tick = false;

	currentTime = (float)glfwGetTime();
	dt = currentTime - lastTime;

	while (dt < 1.0f / frameLimit) {
		currentTime = (float)glfwGetTime();
		dt = currentTime - lastTime;
	}

	Timer::lastTime = Timer::currentTime;
	FPS++;

	if (currentTime - lastSecond >= 1.0f) {
		lastSecond = currentTime;
		//std::cout << "FPS : " << std::to_string((framesPerSecond)) << std::endl;
		FPS = 0;
	}

	if (currentTime - lastTick >= 0.015625f) {
		tick = true;
		lastTick += 0.015625f;
		//Find a more stable Tick method
	}


}
