#include "Collideable.h"

Collideable::Collideable(const CollisionShape * const shape, const glm::vec3 & position, const glm::vec3 & rotation):shape(shape), Object3D(position, rotation)
{
}

bool Collideable::collidesWith(glm::vec3 & point)
{
	//TODO rotate point by -rotation around 0,0,0 before collision
	return shape->collidesWith(point - position);
}
