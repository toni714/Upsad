#include "Camera.h"

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
