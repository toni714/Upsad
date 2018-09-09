#include "CylinerCollision.h"

#include <math.h>

bool CylinderCollision::collidesWith(const glm::vec3 & point) const
{
	return (point.y >= bottom) && (point.y <= top) && (sqrt(pow(point.x, 2) + pow(point.z, 2)) <= radius);
}
