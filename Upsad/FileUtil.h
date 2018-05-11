#pragma once

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Utility.h"

namespace FileUtil {
	std::string loadFile(const char* const filename);
	GLuint load_BMP(const char* const filename);
}