#include "ModelHelper.h"

#include "FileUtil.h"

RawModel * ModelHelper::getModelFromFile(const char * filename)
{
	const auto& modelPosition = models.find(filename);
	if (modelPosition != models.end()) {
		return modelPosition->second;
	}
	else {
		GLuint vaoID = createVAO();
		ModelData modelData = FileUtil::getModelData(filename);

		loadToVAO(vaoID, modelData);

		//TODO maybe make vertex count an size_t
		RawModel* model = new RawModel(vaoID, modelData.indices.size());
		models.insert(std::make_pair(filename, model));

		return model;
	}
}

ImageTexture * ModelHelper::getTextureFromFile(const char * filename)
{
	const auto& texturePosition = textures.find(filename);
	if (texturePosition != textures.end()) {
		return texturePosition->second;
	}
	else {
		GLuint textureID = createTexture();

		loadTextureData(textureID, FileUtil::getBMPData(filename));

		ImageTexture* texture = new ImageTexture(textureID);
		textures.insert(std::make_pair(filename, texture));

		return texture;
	}
}

void ModelHelper::loadTextureData(const GLuint& textureID, const BMPData& textureData) {
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, textureData.colorFormat, GL_UNSIGNED_BYTE, textureData.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint ModelHelper::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

GLuint ModelHelper::createVBO(const GLenum& target)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(target, vboID);
	vbos.push_back(vboID);
	return vboID;
}

GLuint ModelHelper::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
}

template<typename T>
void ModelHelper::bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type)
{
	GLuint bufferID=createVBO(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dimensions, type, GL_FALSE, 0, nullptr);
	glDisableVertexAttribArray(attribute);
}

void ModelHelper::loadToVAO(const GLuint& vaoID, const ModelData& modelData) {
	glBindVertexArray(vaoID);
	bufferData(modelData.vertices, 0, 3, GL_FLOAT);
	bufferData(modelData.uvs, 1, 2, GL_FLOAT);
	bufferData(modelData.normals, 2, 3, GL_FLOAT);

	createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelData.indices.size() * sizeof(GLuint), modelData.indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)
}

void ModelHelper::cleanup()
{
	std::vector<GLuint> textureList;
	for (const auto &textureID : textures) {
		textureList.push_back(textureID.second->id);
		delete textureID.second;
	}
	glDeleteTextures((GLsizei)textureList.size(), textureList.data());

	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());
	std::vector<GLuint> vaoList;

	for (const auto &model : models) {
		vaoList.push_back(model.second->vaoID);
		delete model.second;
	}
	glDeleteVertexArrays((GLsizei)vaoList.size(), vaoList.data());
	models.clear();

	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
		delete[] * it;
	}*/
}

std::unordered_map<std::string, RawModel*> ModelHelper::models;
std::vector<GLuint> ModelHelper::vbos;
std::unordered_map<std::string, ImageTexture*> ModelHelper::textures;
std::vector<uint8_t*> ModelHelper::textureData;