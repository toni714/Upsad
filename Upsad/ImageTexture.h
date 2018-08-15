#pragma once

#include <glad/glad.h>

struct ImageTexture
{
	ImageTexture(const GLuint id) :id(id) {}
	const GLuint id;
	~ImageTexture();
};
