#pragma once

#include <glad/glad.h>

class ImageTexture
{
private:
	GLuint id;
	ImageTexture(const GLuint& textureID);
public:
	ImageTexture() = delete;
	static ImageTexture* loadFromBMP(const char* filename);
	static ImageTexture* createTexture(const GLuint& textureID);
	~ImageTexture();
	GLuint getID() const;
};
