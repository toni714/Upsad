#pragma once

#include "CollisionShape.h"
#include "Object3D.h"

class Collideable : public Object3D {
private:
	const CollisionShape* const shape;
public:
	Collideable(const CollisionShape* const shape, const glm::vec3& position, const glm::vec3& rotation);
	bool collidesWith(glm::vec3& point);
};