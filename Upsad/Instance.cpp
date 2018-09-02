#include "Instance.h"

bool Instance::collidesWith(const glm::vec3 & point)
{
	glm::vec3 localPoint = point - position;
	LimitBox bounding = texturedModel->model->bounding;
	float left = bounding.left;
	float right = bounding.right;
	float top = bounding.top;
	float bottom = bounding.bottom;
	float front = bounding.front;
	float back = bounding.back;
	return (localPoint.x > left) && (localPoint.x < right) && (localPoint.y > bottom) && (localPoint.y < top) && (localPoint.z > front) && (localPoint.z < back);
}
