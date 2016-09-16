#include "Text.h"
#include "Character.h"
#include "Res.h"

#include <iostream>

static float scaleFactor = 512.0f;

Text::Text(Vector2f position, std::string data, Vector2f scale)
{
	this->data = data;
	this->length = data.length();
	this->position = position;
	this->scale = scale;
	this->charsToRender = length*6;
	
	generateVAO();

	int pos_size = data.length() * 6 * 2;
	int tex_size = data.length() * 6 * 2;
	float * pos = new float[pos_size];
	float * tex = new float[tex_size];

	writeCharacterData(data, pos, tex);
	updateVAO(pos, pos_size, tex, tex_size);

	delete[] pos;
	delete[] tex;
}

void Text::writeCharacterData(std::string string, float * pos, float * tex)
{
	float xPointer = 0;
	float yPointer = 0;

	int vertexPointer = 0;
	int texPointer = 0;

	for (int i = 0; string[i] != '\0'; i++) {
		std::string str("");
		str += string[i];

		if (str == "/") {
			yPointer -= Res::getCharacter("I")->height;
			xPointer = 0;
			continue;
		}

		Character* ch = Res::getCharacter(str);

		pos[vertexPointer++] = (xPointer + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / 64.0f;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / 64.0f;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / 64.0f;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / 64.0f;

		pos[vertexPointer++] = (xPointer + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / 64.0f;

		pos[vertexPointer++] = (xPointer + ch->xoffset) / 64.0f;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / 64.0f;

		xPointer += .75f*ch->xadvance;


		tex[texPointer++] = (ch->x) / scaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / scaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / scaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / scaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / scaleFactor;
		tex[texPointer++] = (ch->y) / scaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / scaleFactor;
		tex[texPointer++] = (ch->y) / scaleFactor;

		tex[texPointer++] = (ch->x) / scaleFactor;
		tex[texPointer++] = (ch->y) / scaleFactor;

		tex[texPointer++] = (ch->x) / scaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / scaleFactor;

	}

}

void Text::updateVAO(float * pos, int pos_size, float * tex, int tex_size)
{

	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, pos_size * 4, pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, tex_buffer);
	glBufferData(GL_ARRAY_BUFFER, tex_size * 4, tex, GL_STATIC_DRAW);

}

void Text::generateVAO(){

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &pos_buffer);
	glGenBuffers(1, &tex_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, tex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(1);
}

void Text::setText(std::string str)
{

	this->length = str.length();
	this->data = str;

	glBindVertexArray(VAO);

	int pos_size = str.length() * 6 * 2;
	int tex_size = str.length() * 6 * 2;
	float * pos = new float[pos_size];
	float * tex = new float[tex_size];

	writeCharacterData(str, pos, tex);
	updateVAO(pos, pos_size, tex, tex_size);

	delete[] pos;
	delete[] tex;


}

int Text::getNumberOfVertices()
{
	return 6 * length;
}

bool Text::addCharactersToRender()
{
	if (charsToRender < length * 6) {
		charsToRender += 6;
		return false;
	}
	return true;
}

void Text::draw() {

	ShaderProgram * currentShader = Res::getShader("textShader");

	glActiveTexture(GL_TEXTURE0);
	Res::getTexture("Font")->bind();

	glBindVertexArray(this->VAO);

	currentShader->loadVector2f("pos", this->position);
	currentShader->loadVector2f("scale", this->scale);

	glDrawArrays(GL_TRIANGLES, 0, this->charsToRender);

}
