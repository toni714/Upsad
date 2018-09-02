#include "ModelHelper.h"

#include "OpenGLHelper.h"

std::shared_ptr<RawModel> ModelHelper::getModelFromFile(const std::string & filename)
{
	const auto& modelPosition = INTERNAL::models.find(filename);
	if (modelPosition != INTERNAL::models.end()) {
		return modelPosition->second;
	}
	else {
		GLuint vaoID = OpenGLHelper::createVAO();
		ModelData data = FileHelper::getModelDataFromFile(filename);
		
		std::shared_ptr<RawModel> model=loadModelDataToRawModel(data);

		INTERNAL::models.insert(std::make_pair(filename, model));

		return model;
	}
}

std::shared_ptr<RawModel> ModelHelper::loadModelDataToRawModel(const ModelData& modelData) {
	std::vector<GLfloat> positions;
	std::vector<GLfloat> uv_coordinates;
	std::vector<GLfloat> normals;
	for (const auto& vertex : modelData.vertices) {
		positions.push_back(vertex.position.x);
		positions.push_back(vertex.position.y);
		positions.push_back(vertex.position.z);
		uv_coordinates.push_back(vertex.uv_coordinates.x);
		uv_coordinates.push_back(vertex.uv_coordinates.y);
		normals.push_back(vertex.normal.x);
		normals.push_back(vertex.normal.y);
		normals.push_back(vertex.normal.z);
	}
	
	GLuint vaoID = OpenGLHelper::createVAO();

	GLuint positionsBuffer=OpenGLHelper::createVBO(GL_ARRAY_BUFFER);
	GLuint uvsBuffer = OpenGLHelper::createVBO(GL_ARRAY_BUFFER);
	GLuint normalsBuffer = OpenGLHelper::createVBO(GL_ARRAY_BUFFER);
	
	OpenGLHelper::bufferData(vaoID, positionsBuffer, positions, 0, 3, GL_FLOAT);
	OpenGLHelper::bufferData(vaoID, uvsBuffer, uv_coordinates, 1, 2, GL_FLOAT);
	OpenGLHelper::bufferData(vaoID, normalsBuffer, normals, 2, 3, GL_FLOAT);


	glBindVertexArray(vaoID);
	GLuint vboID = OpenGLHelper::createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelData.indices.size() * sizeof(GLuint), modelData.indices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);			//Is this good practice?
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//Is this good Practice?

	glBindVertexArray(0);	//Unbind VAO (Safety)
	return std::make_shared<RawModel>(vaoID, modelData.indices.size(), positionsBuffer, uvsBuffer, normalsBuffer, modelData.bounding);
}

void ModelHelper::cleanup()
{
	INTERNAL::models.clear();
}

std::unordered_map <std::string, std::shared_ptr<RawModel>> ModelHelper::INTERNAL::models= std::unordered_map <std::string, std::shared_ptr<RawModel>>();