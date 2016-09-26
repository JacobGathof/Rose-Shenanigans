#include "UIManager.h"


Textbox UIManager::textbox;

void UIManager::init(){
	textbox.init();
}

void UIManager::destroy(){
	textbox.destroy();
}

void UIManager::update(){
	textbox.update();
}

void UIManager::tick(){

}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}
