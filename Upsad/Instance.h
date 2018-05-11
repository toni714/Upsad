#pragma once

#include <glm\vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "TexturedModel.h"

class Instance
{
private:
	TexturedModel * texModel;
	glm::vec3 pos;
	glm::vec3 rot;
	int scale;
public:
	Instance(TexturedModel* texModel, const glm::vec3& pos, const glm::vec3& rot, const int& scale);
	~Instance();
	TexturedModel* getTexModel() const;
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;
	int getScale() const;
};
