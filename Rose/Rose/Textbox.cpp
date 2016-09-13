#include "Textbox.h"

Text * Textbox::text;
bool Textbox::isVisible;
bool Textbox::isWriting;
std::queue<std::string> Textbox::queue;

void Textbox::draw()
{
	text->draw();
}

void Textbox::init(){
	isVisible = true;
	isWriting = false;
	text = new Text(Vector2f(0, 0), "Textbox Initialization", Vector2f(4, 4));
}

void Textbox::destroy()
{
	delete text;
}

void Textbox::advanceQueue(){

	if (!queue.empty()) {
		std::string str = queue.front();
		queue.pop();
		text->setText(str);
		text->reset();
	}
	else {
		isVisible = false;
	}

}

void Textbox::update(){

	text->addCharactersToRender();

}

void Textbox::print(std::string message){
	queue.emplace(message);
}
