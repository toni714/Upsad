#pragma once

#include <glad/glad.h>
#include <cstdint>

struct BMPData {
	GLuint width;
	GLuint height;
	GLenum colorFormat;
	uint8_t* pixels;
};