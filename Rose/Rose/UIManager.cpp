#include "UIManager.h"


Textbox UIManager::textbox;
Statbox UIManager::statbox;
UIElement UIManager::tilebox;

void UIManager::init(){
	textbox.init();
	statbox.init();
	tilebox.init();
}

void UIManager::destroy(){
	textbox.destroy();
	statbox.destroy();
	tilebox.destroy();
}

void UIManager::update(){
	textbox.update();
	statbox.update();
	tilebox.update();
}

void UIManager::tick(){

}

void UIManager::drawTextured(){

}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}
