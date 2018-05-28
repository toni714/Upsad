#pragma once

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Vertex.h"
//#include "Utility.h"
#include "StringUtil.h"
#include "OBJWrapper.h"
#include "RawModel.h"
#include "ModelHelper.h"
#include "ModelData.h"
#include "BMPData.h"

class FileUtil {
public:
	static std::string loadFile(const char* const filename);
	static BMPData getBMPData(const char* const filename);
	static ModelData getModelData(const char* filename);
};