#include "Statbox.h"



void Statbox::draw(){

	UIElement::draw();
	text->draw();

}

void Statbox::init(){

	isVisible = true;
	topLeft = Vector2f(-60 * SCALEFACTOR / 64, 60 * SCALEFACTOR / 64);
	botRight = Vector2f(-20 * SCALEFACTOR / 64, 20 * SCALEFACTOR / 64);
	text = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
}

void Statbox::destroy(){
	delete text;
}

void Statbox::update(){
	if (player->statsChanged) {
		text->setText(
			"Level : " + std::to_string(player->level) + 
			"/Name : " + "Eric" + 
			"/EXP : " + std::to_string(player->exp) + 
			"/Age : " + "???" + 
			"/HP : " + std::to_string(player->hp));

		text->position = topLeft + Vector2f(4 * SCALEFACTOR / 64, -4 * SCALEFACTOR / 64);
	}
	player->statsChanged = false;
}

Statbox::Statbox()
{
}


Statbox::~Statbox()
{
}
