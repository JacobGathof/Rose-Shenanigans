#include "Textbox.h"

Text * Textbox::text;
bool Textbox::isVisible;
bool Textbox::isDisplayingText;
bool Textbox::locked;
Vector2f Textbox::topLeft;
Vector2f Textbox::botRight;
std::queue<std::string> Textbox::queue;

void Textbox::draw()
{
	if (isVisible) {

		ShaderProgram * shader = Res::getShader("uiShader");
		shader->loadVector2f("scale", -1*topLeft + botRight);
		shader->loadVector2f("pos", topLeft);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);


		text->draw();
	}
}

void Textbox::init(){
	isVisible = true;
	isDisplayingText = false;
	locked = false;
	topLeft = Vector2f(-60, -32);
	botRight = Vector2f(60, -60);
	text = new Text(Vector2f(0, 0), "", Vector2f(4, 4));
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
		isDisplayingText = true;
		isVisible = true;
		std::string str = queue.front();
		queue.pop();

		text->setText(str);
		text->position = topLeft + Vector2f(4,-4);
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

	text->addCharactersToRender();

}

void Textbox::print(std::string message){
	
	queue.emplace(message);

}
