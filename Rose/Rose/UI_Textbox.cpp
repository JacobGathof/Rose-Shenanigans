#include "UI_Textbox.h"


std::queue<TextObject> Textbox::queue;

void Textbox::draw() {
	Renderer::renderTextbox(this);
}

void Textbox::init() {

	tex = Res::getTexture(Textbox_Tex);
	isVisible = false;
	currentlyWriting = false;
	isDisplayingText = false;
	topLeft = Utils::toScreenCoordinates(-60, -28);
	botRight = Utils::toScreenCoordinates(60, -60);
	text = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
	for (int i = 0; i < 3; i++) {
		answers[i] = new Text(Vector2f(0, 0), "", Vector2f(4 * SCALEFACTOR / 64, 4 * SCALEFACTOR / 64));
	}
}

void Textbox::destroy() {
	delete text;
	for (int i = 0; i < 3; i++) {
		delete answers[i];
	}
}

void Textbox::setSelectedAnswer(int i){

	answers[selectedAnswer]->color = Color(0, 0, 0);
	selectedAnswer += i;
	if (selectedAnswer < 0 || selectedAnswer > 2) selectedAnswer -= i;
	answers[selectedAnswer]->color = Color(1, 0, 0);
}

void Textbox::advanceQueue() {

	isDisplayingText = false;

	if (!queue.empty()) {
		currentlyWriting = true;
		isDisplayingText = true;
		isVisible = true;
		TextObject obj = queue.front();

		std::string str = obj.string;
		bool question = obj.question;
		queue.pop();

		if (question) {
			printQuestion(str);
		}
		else {
			text->setText(str);
			text->position = topLeft + Utils::toScreenCoordinates(4, -4);
			text->reset();
		}
	}
	else {
		isVisible = false;
	}
}

void Textbox::update() {

	if (!queue.empty() && !isDisplayingText) {
		advanceQueue();
	}

	if (text->addCharactersToRender(1))
		currentlyWriting = false;

	if (!isVisible)
		text->reset();
}

void Textbox::print(std::string message, bool question) {
	formatString(message, question);
}

void Textbox::printQuestion(std::string str){
	askingQuestion = true;

	int index = findDelimiter(str, '+');
	std::string t = str.substr(0, index);
	str = str.substr(++index);
	text->setText(t);
	text->position = topLeft + Utils::toScreenCoordinates(4, -4);


	for (int i = 0; i < 3; i++) {
		index = findDelimiter(str, '+');
		if (index == -1) continue;

		std::string m = str.substr(0, index);
		str = str.substr(++index);
		answers[i]->setText(m);
		answers[i]->position = topLeft + Utils::toScreenCoordinates(4, -10-6*i);
	}

	answers[0]->color = Color(1, 0, 0);
}

void Textbox::formatString(std::string str, bool question) {

	/*
	int currentIndex = 0;

	for (int i = 0; i < 4; i++) {
		if (str.length() - currentIndex > 40) {
			currentIndex = findIndex(str, 40 + currentIndex - 40, 40 + currentIndex);
			str.replace(currentIndex, 1, "/");
		}
	}

	if (str.length() - currentIndex > 40) {
		currentIndex = findIndex(str, 40 + currentIndex - 40, 40 + currentIndex);

		queue.emplace(str.substr(0, currentIndex));
		print(str.substr(currentIndex));
		return str;
	}

	queue.emplace(str);
	return str;
	*/
	TextObject t{ str, question };
	queue.emplace(t);

}

int Textbox::findIndex(std::string str, int start, int end) {
	for (int i = end; i > start; i--) {
		if (str[i] == ' ')
			return i;
	}
	return -1;
}

int Textbox::findDelimiter(std::string str, char d){

	int counter = 0;
	int max = str.size();
	while (counter < str.size()) {
		if (str[counter] == d) return counter;
		counter++;
	}

	return -1;
}

#pragma endregion