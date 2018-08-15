#include "ImageTexture.h"

ImageTexture::~ImageTexture()
{
	glDeleteTextures(1, &id);
}