#pragma once

#include "CollisionShape.h"

class CylinderCollision : public CollisionShape {
private:
	float top;
	float bottom;
	float radius;
public:
	bool collidesWith(const glm::vec3& point)const;
	CylinderCollision(float top, float bottom, float radius) :top(top), bottom(bottom), radius(radius) {};
};