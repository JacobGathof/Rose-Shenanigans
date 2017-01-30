#include "UI_Title.h"
#include "Timer.h"
#include "Input.h"

void Title::draw() {
	Renderer::renderTitle(this);
}

void Title::init() {

	opacity = 0.0f;
	tex = Res::getTexture(Default);
	textured = 0;
	isVisible = true;
	topLeft = Utils::toScreenCoordinates(-64, 2);
	botRight = Utils::toScreenCoordinates(64, -20);
	text = new Text(Vector2f(0, 0), "Narcissus/<Sin of Pride>", Vector2f(6 * SCALEFACTOR / 64, 6 * SCALEFACTOR / 64), true, Color(0,.25f,1), 1.0f);
	text->charsToRender = 0;
}

void Title::destroy() {
	delete text;
}


void Title::update() {

	if (Input::testVar) {

		if (!rising && !falling && currentIdle == 0.0f) {
			rising = true;
			falling = false;
			text->opacity = 1.0f;
		}

		if (rising) {
			opacity += .5f*Timer::dt;
		}

		if (opacity >= .5f) {
			rising = false;
			opacity = .5f;
			currentIdle += 1.0f*Timer::dt;
		}
		
		if (currentIdle > 0.0f && currentIdle < 2.0f) {
			if (Timer::tick) {
				letterBuffer--;
			}
			if (letterBuffer == 0) {
				text->addCharactersToRender();
				letterBuffer = 10;
			}
		}

		if (currentIdle >= 2.0f) {
			falling = true;
			opacity -= .5f*Timer::dt;
			text->opacity -= 1.0f*Timer::dt;
		}

		if (falling && opacity <= 0.0) {
			rising = false;
			falling = false;
			toDisplay = false;
			Input::testVar = false;
			text->charsToRender = 0;
			currentIdle = 0.0f;
		}



	}


}
