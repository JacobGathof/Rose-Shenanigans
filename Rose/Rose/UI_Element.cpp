#include "UI_Element.h"


UIElement::UIElement(){

	topLeft = Utils::toScreenCoordinates(40,40);
	botRight = Utils::toScreenCoordinates(60, 60);
	opacity = 0.50f;
	isVisible = true;

}

void UIElement::draw(){
	Renderer::renderDefaultUIElement(this);
}


void UIElement::init(){}
void UIElement::destroy(){}
void UIElement::update(){}
UIElement::~UIElement() {}

#pragma endregion




#pragma region Inventory_Screen

Inventory_Screen::Inventory_Screen(Player *player) {
	this->player = player;
}

Inventory_Screen::~Inventory_Screen()
{
	delete player;
}

void Inventory_Screen::init()
{
	topLeft = Utils::toScreenCoordinates(-60, 60);
	botRight = Utils::toScreenCoordinates(-20, 20);
}

void Inventory_Screen::draw()
{
	//Renderer::renderInventoyScreen(&(player->inventory.weapons.at(0)), player->inventory.BackDrop, player->inventory.weapons.size());
}




