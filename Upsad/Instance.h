#pragma once

#include <glm\vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "RawModel.h"

class Instance
{
private:
	RawModel * model;
	glm::vec3 pos;
	glm::vec3 rot;
	int scale;
public:
	Instance(RawModel* model, const glm::vec3& pos, const glm::vec3& rot, const int& scale);
	~Instance();
	RawModel* getModel() const;
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;
	int getScale() const;
};

