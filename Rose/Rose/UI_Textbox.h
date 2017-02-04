#pragma once
#include "UI_Element.h"
#define Textbox UI_Textbox

struct TextObject {
	std::string string;
	bool question;
};

class Textbox : public UIElement
{
public:

	Text * text;
	bool isDisplayingText;
	bool currentlyWriting;
	bool askingQuestion;
	int selectedAnswer;

	Text * answers[3];

	static std::queue<TextObject> queue;

	virtual void draw();
	virtual void init();
	virtual void destroy();
	virtual void update();

	void setSelectedAnswer(int i);
	void advanceQueue();
	void print(std::string message, bool question = false);
	void printQuestion(std::string str);

	void formatString(std::string str, bool question);
	int findIndex(std::string str, int start, int end);
	int findDelimiter(std::string str, char d);
};