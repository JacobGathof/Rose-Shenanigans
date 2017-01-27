#include "UI_Skillbox.h"



Skillbox::Skillbox() {}

void Skillbox::init() {
	topLeft = Utils::toScreenCoordinates(-60, 60);
	botRight = Utils::toScreenCoordinates(-20, 20);
}

void Skillbox::draw(Player *player) {
	int i = 0;
	for each (Skill s in player->skills)
	{
		++i;
		Renderer::renderSkill(&s, i);
	}
}