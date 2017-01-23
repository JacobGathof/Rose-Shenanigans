#include "Text.h"
#include "Res.h"
#include "Renderer.h"
#include <iostream>

static float textureScaleFactor = 512.0f;
static float textScaleFactor = 64.0f;

Text::Text(Vector2f position, std::string data, Vector2f scale, bool centered)
{
	this->data = data;
	this->length = data.length();
	this->position = position;
	this->scale = scale;
	this->charsToRender = length*6;

	if (centered) {
		this->position.x -= this->scale.x/SCALEFACTOR*64.0f*.5f*toScreenCoordinates(this->length*Res::getCharacter(" ")->xadvance, 0).x / textScaleFactor;
	}
	
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
			yPointer -= 1.25f*Res::getCharacter("I")->height;
			xPointer = 0;
			continue;
		}

		Character* ch = Res::getCharacter(str);

		pos[vertexPointer++] = (xPointer + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / textScaleFactor;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / textScaleFactor;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / textScaleFactor;

		pos[vertexPointer++] = (xPointer + ch->width + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / textScaleFactor;

		pos[vertexPointer++] = (xPointer + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->yoffset) / textScaleFactor;

		pos[vertexPointer++] = (xPointer + ch->xoffset) / textScaleFactor;
		pos[vertexPointer++] = (yPointer + -ch->height - ch->yoffset) / textScaleFactor;

		xPointer += 1.00f*ch->xadvance;


		tex[texPointer++] = (ch->x) / textureScaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / textureScaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / textureScaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / textureScaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / textureScaleFactor;
		tex[texPointer++] = (ch->y) / textureScaleFactor;

		tex[texPointer++] = (ch->x + ch->width) / textureScaleFactor;
		tex[texPointer++] = (ch->y) / textureScaleFactor;

		tex[texPointer++] = (ch->x) / textureScaleFactor;
		tex[texPointer++] = (ch->y) / textureScaleFactor;

		tex[texPointer++] = (ch->x) / textureScaleFactor;
		tex[texPointer++] = (ch->y + ch->height) / textureScaleFactor;

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
	this->charsToRender = length * 6;

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

bool Text::addCharactersToRender(int n)
{
	for (int i = 0; i < n; i++) {
		if (charsToRender < length * 6) {
			charsToRender += 6;
			return false;
		}
	}
	return true;
}

void Text::draw() {
	Renderer::renderText(this);
}

Vector2f Text::toScreenCoordinates(int x, int y) {
	return Vector2f(x*SCALEFACTOR / 64, y*SCALEFACTOR / 64);
}


Character::Character(std::vector<int> data)
{
	ID = (char)data[0];
	x = data[1];
	y = data[2];
	width = data[3];
	height = data[4];
	xoffset = data[5];
	yoffset = data[6];
	xadvance = data[7];

}
