#include "UIManager.h"


Textbox UIManager::textbox;
Statbox UIManager::statbox;

void UIManager::init(){
	textbox.init();
	statbox.init();
}

void UIManager::destroy(){
	textbox.destroy();
	statbox.destroy();
}

void UIManager::update(){
	textbox.update();
	statbox.update();
}

void UIManager::tick(){

}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}
