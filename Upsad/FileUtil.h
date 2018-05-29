#pragma once

#include <glad/glad.h>
#include <fstream>
#include <string>

#include "OBJWrapper.h"
#include "ModelData.h"
#include "BMPData.h"

class FileUtil {
public:
	static std::string loadFile(const char* const filename);
	static BMPData getBMPData(const char* const filename);
	static ModelData getModelData(const char* filename);
};