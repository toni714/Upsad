#include "Instance.h"

Instance::Instance(RawModel* model, const glm::vec3& pos, const glm::vec3& rot, const int& scale)
	:model(model),pos(pos),rot(rot),scale(scale)
{
}

Instance::~Instance()
{
}

RawModel * Instance::getModel() const
{
	return model;
}

glm::vec3 Instance::getPos() const
{
	return pos;
}

glm::vec3 Instance::getRot() const
{
	return rot;
}

int Instance::getScale() const
{
	return scale;
}
