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
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(T), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dimensions, type, GL_FALSE, 0, nullptr);
}

RawModel * ModelHelper::loadToVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
	GLuint vaoID=createVAO();

	bufferData(vertices, 0, 3, GL_FLOAT);

	
	createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);	//Unbind VAO (Safety)

	return new RawModel(vaoID, static_cast<int>(indices.size()));
}

ModelHelper::~ModelHelper()
{
	glDeleteBuffers(static_cast<int>(vbos.size()), vbos.data());
	glDeleteVertexArrays(static_cast<int>(vaos.size()), vaos.data());
}