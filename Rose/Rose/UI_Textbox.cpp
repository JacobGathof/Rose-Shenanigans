#include "UI_Textbox.h"


std::queue<std::string> Textbox::queue;

void Textbox::draw() {
	Renderer::renderTextbox(this);
}

void Textbox::init() {

	tex = Res::getTexture("Textbox");
	isVisible = true;
	currentlyWriting = false;
	isDisplayingText = false;
	locked = false;
	topLeft = toScreenCoordinates(-60, -28);
	botRight = toScreenCoordinates(60, -60);
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
		text->position = topLeft + toScreenCoordinates(4, -4);
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