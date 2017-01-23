#include "UI_Manager.h"


UIElement UIManager::tilebox;
Textbox UIManager::textbox;
Statbox UIManager::statbox;
Skillbox UIManager::skillbox;
Title UIManager::title;

void UIManager::init() {
	textbox.init();
	statbox.init();
	tilebox.init();
	skillbox.init();
	title.init();
}

void UIManager::destroy() {
	textbox.destroy();
	statbox.destroy();
	title.destroy();
}

void UIManager::update() {
	textbox.update();
	statbox.update();
	title.update();
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