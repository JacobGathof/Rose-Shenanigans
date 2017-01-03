#include "UI_Element.h"


UIElement::UIElement(){

	topLeft = toScreenCoordinates(40,40);
	botRight = toScreenCoordinates(60, 60);
	isVisible = true;

}

void UIElement::draw(){
	Renderer::renderDefaultUIElement(this);
}


void UIElement::init(){}
void UIElement::destroy(){}
void UIElement::update(){}
UIElement::~UIElement() {}

Vector2f UIElement::toScreenCoordinates(int x, int y){
	return Vector2f(x*SCALEFACTOR / 64, y*SCALEFACTOR/64);
}

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
	topLeft = toScreenCoordinates(-60, 60);
	botRight = toScreenCoordinates(-20, 20);
}

void Inventory_Screen::draw()
{
	//Renderer::renderInventoyScreen(&(player->inventory.weapons.at(0)), player->inventory.BackDrop, player->inventory.weapons.size());
}




