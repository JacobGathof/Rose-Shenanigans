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
bool Timer::slow = false;
sf::Clock Timer::clock;

void Timer::wait(){

	tick = false;

	currentTime = clock.getElapsedTime().asSeconds();
	dt = currentTime - lastTime;

	while (dt < 1.0f / frameLimit) {
		currentTime = clock.getElapsedTime().asSeconds();
		dt = currentTime - lastTime;
	}

	Timer::lastTime = Timer::currentTime;
	FPS++;

	if (currentTime - lastSecond >= 1.0f) {
		lastSecond = currentTime;
		//std::cout << "FPS : " << std::to_string((framesPerSecond)) << std::endl;
		FPS = 0;
	}

	if (currentTime - lastTick >= 0.125f) {
		tick = true;
		lastTick += 0.125f;
		//Find a more stable Tick method
	}

	if (slow) {
		dt = dt / 4.0f;
	}

}
