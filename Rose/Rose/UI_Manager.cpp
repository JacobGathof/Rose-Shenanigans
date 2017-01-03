#include "UI_Manager.h"


UIElement UIManager::tilebox;
Textbox UIManager::textbox;
Statbox UIManager::statbox;
Skillbox UIManager::skillbox;

void UIManager::init() {
	textbox.init();
	statbox.init();
	tilebox.init();
	skillbox.init();
}

void UIManager::destroy() {
	textbox.destroy();
	statbox.destroy();
}

void UIManager::update() {
	textbox.update();
	statbox.update();
}

void UIManager::tick() {

}

void UIManager::drawTextured() {

}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}