#pragma once

#include <glad/glad.h>
#include <fstream>
#include <string>

#include "OBJWrapper.h"
#include "ModelData.h"
#include "BMPData.h"

class FileUtil {
private:
	static const WORD BITMAP_SIGNATURE = 0x4D42;
	static const GLenum COLOR_LOADING_FORMAT = GL_BGR;

	static std::ifstream openFile(const char* filename);
	template<typename T>
	static T readValueFromFile(std::ifstream& file, const std::streampos& offset);
	static uint8_t* readPixelDataFromBitmap(std::ifstream& file, const DWORD& dataOffset, const DWORD& imageSize);
	static bool hasValidBitmapSignature(std::ifstream& file);
public:
	static std::string loadFile(const char* const filename);
	static BMPData getBMPData(const char* const filename);
	static ModelData getModelData(const char* filename);
};

template<typename T>
inline T FileUtil::readValueFromFile(std::ifstream & file, const std::streampos& offset)
{
	T value;
	file.seekg(offset);
	file.read((char*)&value, sizeof(T));
	return value;
}
