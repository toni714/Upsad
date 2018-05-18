#pragma once

#include <glm/vec3.hpp>

class Light {
private:
	glm::vec3 pos;
	glm::vec3 color;
public:
	Light(glm::vec3 pos, glm::vec3 color);
	glm::vec3 getPos() const;
	glm::vec3 getColor() const;
};