#include "Textbox.h"
#include <iostream>

Text * Textbox::text;
bool Textbox::isVisible;
bool Textbox::isDisplayingText;
bool Textbox::currentlyWriting;
bool Textbox::locked;
Vector2f Textbox::topLeft;
Vector2f Textbox::botRight;
std::queue<std::string> Textbox::queue;

void Textbox::draw()
{
	if (isVisible) {

		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadVector2f("scale", -1*topLeft + botRight);
		shader->loadVector2f("pos", topLeft);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

		text->draw();
	}
}

void Textbox::init(){
	isVisible = false;
	currentlyWriting = false;
	isDisplayingText = false;
	locked = false;
	topLeft = Vector2f(-60 * SCALEFACTOR / 64, -32 * SCALEFACTOR / 64);
	botRight = Vector2f(60* SCALEFACTOR / 64, -60* SCALEFACTOR / 64);
	text = new Text(Vector2f(0, 0), "", Vector2f(4* SCALEFACTOR / 64, 4* SCALEFACTOR / 64));
}

void Textbox::destroy()
{
	delete text;
}

void Textbox::lock()
{
	locked = true;
}

void Textbox::unlock()
{
	locked = false;
}

void Textbox::advanceQueue(){

	if (locked) return;

	isDisplayingText = false;

	if (!queue.empty()) {
		currentlyWriting = true;
		isDisplayingText = true;
		isVisible = true;
		std::string str = queue.front();
		queue.pop();
		
		text->setText(str);
		text->position = topLeft + Vector2f(4* SCALEFACTOR / 64,-4* SCALEFACTOR / 64);
		text->reset();
	}
	else {
		isVisible = false;
	}
}

void Textbox::update(){

	if (!queue.empty() && !isDisplayingText) {
		advanceQueue();
	}

	if (text->addCharactersToRender())
		currentlyWriting = false;

}

void Textbox::print(std::string message){
	
	queue.emplace(message);

}
