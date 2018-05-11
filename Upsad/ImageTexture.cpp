#include "ImageTexture.h"

ImageTexture::ImageTexture(GLuint textureID)
	:id(textureID)
{
}

ImageTexture::~ImageTexture()
{
}

GLuint ImageTexture::getID() const
{
	return id;
}