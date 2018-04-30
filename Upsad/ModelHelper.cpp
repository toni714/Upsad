#include "ModelHelper.h"

RawModel * ModelHelper::loadToVAO(std::vector<GLfloat> vertices) {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//Create and Load Positions VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vaos.push_back(vaoID);
	vbos.push_back(vboID);

	return new RawModel(vaoID, static_cast<int>(vertices.size()));
}

ModelHelper::~ModelHelper()
{
	glDeleteBuffers(static_cast<int>(vbos.size()), vbos.data());
	glDeleteVertexArrays(static_cast<int>(vaos.size()), vaos.data());
}