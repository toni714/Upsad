#pragma once

#include <glad\glad.h>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "RawModel.h"
#include "ImageTexture.h"
#include "ModelData.h"
#include "BMPData.h"

class ModelHelper {
private:
	static std::unordered_map<std::string, RawModel*> models;
	static std::vector<GLuint> vbos;
	static std::unordered_map<std::string, ImageTexture*> textures;
	static std::vector<uint8_t*> textureData;
	static GLuint createVAO();
	static GLuint createVBO(const GLenum& target);
	static GLuint createTexture();
	template<typename T>
	static void bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type);
	static void loadToVAO(const GLuint& vaoID, const ModelData& modelData);
	static void loadTextureData(const GLuint& textureID, const BMPData& textureData);
public:
	ModelHelper() = delete;
	~ModelHelper() = delete;
	static RawModel* getModelFromFile(const char* filename);
	static ImageTexture* getTextureFromFile(const char* filename);
	static void cleanup();
};