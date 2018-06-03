#include "Camera.h"

Camera::Camera(const glm::vec3 & position, const glm::vec3 rotation)
	:position(position),rotation(rotation)
{
}

glm::vec3 Camera::getRotation() const
{
	return rotation;
}

glm::vec3 Camera::getPosition() const
{
	return position;
}

void Camera::rotateBy(const glm::vec3 & rotation)
{
	this->rotation += rotation;
}

void Camera::moveBy(const glm::vec3 & movement)
{
	position += movement;
}

void Camera::moveForward(const float & amount)
{
	position.x += amount*sin(-rotation.y);
	position.z += amount*(-cos(rotation.y));
}

void Camera::moveSideways(const float & amount)
{
	position.x += amount * cos(rotation.y);
	position.z += amount * (-sin(rotation.y));
}
