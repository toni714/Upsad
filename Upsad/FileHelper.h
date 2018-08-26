#pragma once

#include <fstream>

#include "ModelData.h"
#include "Vertex.h"
#include "BMPData.h"
#include "RawModel.h"
#include "ImageTexture.h"
#include <memory>
#include <unordered_map>

class FileHelper {
private:
	static const WORD BITMAP_SIGNATURE = 0x4D42;
	static const GLenum COLOR_LOADING_FORMAT = GL_BGR;

	static std::ifstream openFile(const char* filename);
	template<typename T>
	static T readValueFromFile(std::ifstream& file, const std::streampos& offset);
	static uint8_t* readPixelDataFromBitmap(std::ifstream& file, const DWORD& dataOffset, const DWORD& imageSize);
	static bool hasValidBitmapSignature(std::ifstream& file);

	static std::unordered_map<std::string, std::shared_ptr<ImageTexture>> textures;
	static std::vector<uint8_t*> textureData;
	static GLuint createTexture();
	
	static void loadTextureData(GLuint textureID, const BMPData& textureData);

public:
	static std::string loadFileToString(const std::string& filename);
	static BMPData getBMPData(const char* const filename);

	static ModelData getModelDataFromFile(const std::string& filename);

	static std::shared_ptr<ImageTexture> getTextureFromFile(const char* filename);
	static void cleanup();
};

template<typename T>
inline T FileHelper::readValueFromFile(std::ifstream & file, const std::streampos& offset)
{
	T value;
	file.seekg(offset);
	file.read((char*)&value, sizeof(T));
	return value;
}
