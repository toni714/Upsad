#pragma once

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Utility.h"
#include "TexturedModel.h"
#include "StringUtil.h"
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Vertex.h"
#include "Utility.h"

namespace FileUtil {
	std::string loadFile(const char* const filename);
	GLuint load_BMP(const char* const filename);
	RawModel* loadOBJ(const char* filename);
}