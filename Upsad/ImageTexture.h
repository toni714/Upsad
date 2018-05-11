#pragma once

#include <glad/glad.h>

class ImageTexture
{
private:
	GLuint id;
public:
	ImageTexture(GLuint textureID);
	~ImageTexture();
	GLuint getID() const;
};

