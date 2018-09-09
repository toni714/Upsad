#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include "Instance.h"

class World {
public:
	std::vector<Instance*> instances;//TODO make this private
	bool isSpaceFree(const glm::vec3& space);
};