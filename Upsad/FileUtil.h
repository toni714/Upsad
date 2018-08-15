#pragma once

#include <fstream>

#include "ModelData.h"
#include "BMPData.h"
#include "RawModel.h"
#include "ImageTexture.h"
#include <unordered_map>
#include <memory>

class FileUtil {
private:
	static const WORD BITMAP_SIGNATURE = 0x4D42;
	static const GLenum COLOR_LOADING_FORMAT = GL_BGR;

	static std::ifstream openFile(const char* filename);
	template<typename T>
	static T readValueFromFile(std::ifstream& file, const std::streampos& offset);
	static uint8_t* readPixelDataFromBitmap(std::ifstream& file, const DWORD& dataOffset, const DWORD& imageSize);
	static bool hasValidBitmapSignature(std::ifstream& file);

	static std::unordered_map<std::string, std::shared_ptr<RawModel>> models;
	static std::vector<GLuint> vbos;
	static std::unordered_map<std::string, std::shared_ptr<ImageTexture>> textures;
	static std::vector<uint8_t*> textureData;
	static GLuint createVAO();
	static GLuint createVBO(const GLenum& target);
	static GLuint createTexture();
	template<typename T>
	static void bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type);
	static void loadModelToVAO(const GLuint& vaoID, const ModelData& modelData);
	static void loadTextureData(const GLuint& textureID, const BMPData& textureData);

public:
	static std::string loadFileToString(const char* const filename);
	static BMPData getBMPData(const char* const filename);
	static ModelData getModelData(const char* filename);


	static std::shared_ptr<RawModel> getModelFromFile(const char* filename);
	static std::shared_ptr<ImageTexture> getTextureFromFile(const char* filename);
	static void cleanup();
};

template<typename T>
inline T FileUtil::readValueFromFile(std::ifstream & file, const std::streampos& offset)
{
	T value;
	file.seekg(offset);
	file.read((char*)&value, sizeof(T));
	return value;
}
