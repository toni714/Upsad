#include "ModelHelper.h"

RawModel * ModelHelper::loadToVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);	//Create Model
	glBindVertexArray(vaoID);		//Bind Model

	//Create and Load Positions VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);		//Create Positions VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID);	//Bind Positions VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);//Buffer Vertex Positions


	//EXTRACT

	glEnableVertexAttribArray(0);														//Enable Positions Attribute
	//             location, dimensions, type, normalized, dim*size(type), offset(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);	//Bind Positions Attribute

	//EXTRACT


	GLuint iboID;
	glGenBuffers(1, &iboID);						//Create Index-Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);	//Bind Index-Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)

	vaos.push_back(vaoID);
	vbos.push_back(vboID);
	vbos.push_back(iboID);

	return new RawModel(vaoID, static_cast<int>(indices.size()));
}

ModelHelper::~ModelHelper()
{
	glDeleteBuffers(static_cast<int>(vbos.size()), vbos.data());
	glDeleteVertexArrays(static_cast<int>(vaos.size()), vaos.data());
}