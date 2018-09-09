#include "World.h"

bool World::isSpaceFree(const glm::vec3 & space)
{
	bool collision = false;
	for (const auto& instance : instances) {
		if (instance->collidesWith(space)) {
			//__debugbreak();
			collision = true;
		}
	}
	return !collision;
}