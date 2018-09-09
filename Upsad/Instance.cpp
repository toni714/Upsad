#include "Instance.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool Instance::collidesWith(const glm::vec3 & globalPoint)const 
{
	//TODO inverse transformation not working
	//glm::vec4 global4Point = glm::vec4(globalPoint, 0);
	//glm::vec4 transformationResult = glm::inverse(getModelMatrix()) * global4Point;
	//glm::vec3 localPoint = glm::vec3(transformationResult.x, transformationResult.y, transformationResult.z);
	//__debugbreak();
	return texturedModel->model->bounding->collidesWith(globalPoint-position);
}

glm::mat4 Instance::getModelMatrix()const
{
	glm::mat4 modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
	return modelMatrix;
}
