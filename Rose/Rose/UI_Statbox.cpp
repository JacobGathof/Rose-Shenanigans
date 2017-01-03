#include "UI_Statbox.h"


void Statbox::draw() {
	Renderer::renderStatbox(this);
}

void Statbox::init() {

	tex = Res::getTexture("Statbox");
	isVisible = true;
	topLeft = toScreenCoordinates(-60, 60);
	botRight = toScreenCoordinates(-20, 20);
	text = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
}

void Statbox::destroy() {
	delete text;
}

void Statbox::update() {
	if (player->statsChanged) {
		text->setText(
			"Level : " + std::to_string(player->level) +
			"/Name : " + "Era" +
			"/EXP : " + std::to_string(player->exp) +
			"/Age : " + "???" +
			"/HP : " + std::to_string(player->hp));

		text->position = topLeft + toScreenCoordinates(4, -4);
	}
	player->statsChanged = false;
}

Statbox::Statbox() {}

Statbox::~Statbox() {}


