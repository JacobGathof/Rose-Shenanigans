#include "Screen.h"



bool Screen::fadingBlack = false;
bool Screen::fadingWhite = false;
bool Screen::returning = false;
float Screen::black;
float Screen::white;
float Screen::currentMax;

void Screen::fadeWhite(float duration){
	reset();
	fadingWhite = true;
	currentMax = duration;
}

void Screen::fadeBlack(float duration){

	reset();
	fadingBlack = true;
	currentMax = duration;
}

void Screen::update(float dt){

	if (fadingBlack) {
		black += ((returning) ? -1:1) * dt * 1 / currentMax;
	}
	if (fadingWhite) {
		white += ((returning) ? -1 : 1) * dt * 1 / currentMax;
	}

	if (black >= 1.25f || white >= 1.25f) {
		returning = true;
	}

	if (black < 0.00f || white < 0.00f) {
		reset();
	}
}

void Screen::reset(){
	black = 0;
	white = 0;
	fadingWhite = false;
	fadingBlack = false;
	returning = false;
}
