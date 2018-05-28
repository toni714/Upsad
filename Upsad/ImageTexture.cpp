#include "ImageTexture.h"
#include "FileUtil.h"

ImageTexture::ImageTexture(const GLuint& textureID)
	:id(textureID)
{
}

ImageTexture * ImageTexture::loadFromBMP(const char * filename)
{
	return ModelHelper::getTextureFromFile(filename);
}

ImageTexture * ImageTexture::createTexture(const GLuint & textureID)
{
	return new ImageTexture(textureID);
}

ImageTexture::~ImageTexture()
{
}

GLuint ImageTexture::getID() const
{
	return id;
}