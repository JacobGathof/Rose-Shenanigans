#include "UIElement.h"



#pragma region UIELEMENT
UIElement::UIElement(){

	topLeft = Vector2f(40 * SCALEFACTOR / 64, 40 * SCALEFACTOR / 64);
	botRight = Vector2f(60 * SCALEFACTOR / 64, 60 * SCALEFACTOR / 64);
	isVisible = true;

}

UIElement::~UIElement(){}

void UIElement::draw()
{
	if (isVisible) {
		this->tex->bind();
		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadVector2f("scale", -1 * topLeft + botRight);
		shader->loadVector2f("pos", topLeft);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
	}
}

void UIElement::init(){}

void UIElement::destroy(){}

void UIElement::update(){}

#pragma endregion


#pragma region STATBOX


void Statbox::draw() {

	UIElement::draw();
	text->draw();

}

void Statbox::init() {

	tex = Res::getTexture("Default");
	isVisible = true;
	topLeft = Vector2f(-60 * SCALEFACTOR / 64, 60 * SCALEFACTOR / 64);
	botRight = Vector2f(-20 * SCALEFACTOR / 64, 20 * SCALEFACTOR / 64);
	text = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
}

void Statbox::destroy() {
	delete text;
}

void Statbox::update() {
	if (player->statsChanged) {
		text->setText(
			"Level : " + std::to_string(player->level) +
			"/Name : " + "Eric" +
			"/EXP : " + std::to_string(player->exp) +
			"/Age : " + "???" +
			"/HP : " + std::to_string(player->hp));

		text->position = topLeft + Vector2f(4 * SCALEFACTOR / 64, -4 * SCALEFACTOR / 64);
	}
	player->statsChanged = false;
}

Statbox::Statbox(){}

Statbox::~Statbox(){}



#pragma endregion


#pragma region TEXTBOX

std::queue<std::string> Textbox::queue;

void Textbox::draw()
{
	if (isVisible) {
		UIElement::draw();
		text->draw();
	}
}

void Textbox::init() {

	tex = Res::getTexture("Textbox");
	isVisible = false;
	currentlyWriting = false;
	isDisplayingText = false;
	locked = false;
	topLeft = Vector2f(-48 * SCALEFACTOR / 64, -28 * SCALEFACTOR / 64);
	botRight = Vector2f(48 * SCALEFACTOR / 64, -60 * SCALEFACTOR / 64);
	text = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
}

void Textbox::destroy() {
	delete text;
}

void Textbox::lock() {
	locked = true;
}

void Textbox::unlock() {
	locked = false;
}

void Textbox::advanceQueue() {

	if (locked) return;

	isDisplayingText = false;

	if (!queue.empty()) {
		currentlyWriting = true;
		isDisplayingText = true;
		isVisible = true;
		std::string str = queue.front();
		queue.pop();

		text->setText(str);
		text->position = topLeft + Vector2f(4 * SCALEFACTOR / 64, -4 * SCALEFACTOR / 64);
		text->reset();
	}
	else {
		isVisible = false;
	}
}

void Textbox::update() {

	if (!queue.empty() && !isDisplayingText) {
		advanceQueue();
	}

	if (text->addCharactersToRender())
		currentlyWriting = false;

	if (!isVisible)
		text->reset();
}

void Textbox::print(std::string message) {
	//One line is 37 characters long
	message = splitString(message);
	//queue.emplace(message);
}

std::string Textbox::splitString(std::string str) {

	int currentIndex = 0;

	for (int i = 0; i < 4; i++) {
		if (str.length() - currentIndex > 37) {
			currentIndex = findIndex(str, 37 + currentIndex - 37, 37 + currentIndex);
			str.replace(currentIndex, 1, "/");
		}
	}

	if (str.length() - currentIndex > 37) {
		currentIndex = findIndex(str, 37 + currentIndex - 37, 37 + currentIndex);

		queue.emplace(str.substr(0, currentIndex));
		print(str.substr(currentIndex));
		return str;
	}

	queue.emplace(str);
	return str;

}

int Textbox::findIndex(std::string str, int start, int end) {
	for (int i = end; i > start; i--) {
		if (str[i] == ' ')
			return i;
	}
	return -1;
}

#pragma endregion

