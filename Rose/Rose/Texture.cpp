#include "Texture.h"
#include <iostream>
#include "lodepng.h"


void Texture::bind()
{
	glBindTexture(textureType, tbo);
}

Texture::Texture(char* filename)
{
	textureType = GL_TEXTURE_2D;
	std::vector<unsigned char> image;
	unsigned width, height;

	lodepng::decode(image, width, height, filename);

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

}


Texture::~Texture()
{
	glDeleteBuffers(1, &tbo);
}
