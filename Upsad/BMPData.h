#pragma once

#include <glad/glad.h>
#include <cstdint>

struct BMPData {
	GLuint width;
	GLuint height;
	uint8_t* pixels;
};