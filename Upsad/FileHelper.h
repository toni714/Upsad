#pragma once

#include <fstream>

#include "ModelData.h"
#include "BMPData.h"
#include <memory>
#include <unordered_map>

namespace FileHelper {
	namespace INTERNAL {
		const WORD BITMAP_SIGNATURE = 0x4D42;
		const GLenum COLOR_LOADING_FORMAT = GL_BGR;

		std::ifstream openFile(const std::string& filename);
		template<typename T>
		T readValueFromFile(std::ifstream& file, const std::streampos& offset);
		uint8_t* readPixelDataFromBitmap(std::ifstream& file, const DWORD& dataOffset, const DWORD& imageSize);
		bool hasValidBitmapSignature(std::ifstream& file);
	}

	std::string loadFileToString(const std::string& filename);
	BMPData getBMPDataFromFile(const std::string& filename);
	ModelData getModelDataFromFile(const std::string& filename);
};

template<typename T>
T FileHelper::INTERNAL::readValueFromFile(std::ifstream & file, const std::streampos& offset)
{
	T value;
	file.seekg(offset);
	file.read((char*)&value, sizeof(T));
	return value;
}
