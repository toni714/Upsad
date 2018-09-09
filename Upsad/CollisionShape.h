#pragma once

#include <glm/vec3.hpp>

class CollisionShape {
public:
	virtual bool collidesWith(const glm::vec3& point)const = 0;
};