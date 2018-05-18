#include "ModelHelper.h"

GLuint ModelHelper::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
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

template<typename T>
void ModelHelper::bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type)
{
	createVBO(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dimensions, type, GL_FALSE, 0, nullptr);
	glDisableVertexAttribArray(attribute);
}

RawModel * ModelHelper::loadToVAO(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& uvs, const std::vector<GLfloat>& normals, const std::vector<GLuint>& indices) {
	GLuint vaoID = createVAO();

	bufferData(vertices, 0, 3, GL_FLOAT);
	bufferData(uvs, 1, 2, GL_FLOAT);
	bufferData(normals, 2, 3, GL_FLOAT);

	createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)

	return new RawModel(vaoID, indices.size());
}

GLuint ModelHelper::loadTexture(GLuint width, GLuint height, uint8_t * data)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLint mode = GL_RGB;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures.push_back(textureID);
	textureData.push_back(data);
	return textureID;
}

ModelHelper::~ModelHelper()
{
	glDeleteTextures(textures.size(), textures.data());

	glDeleteBuffers(vbos.size(), vbos.data());
	glDeleteVertexArrays(vaos.size(), vaos.data());

	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
		delete[] * it;
	}*/
}