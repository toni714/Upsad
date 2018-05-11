#include "Instance.h"

Instance::Instance(TexturedModel* texModel, const glm::vec3& pos, const glm::vec3& rot, const int& scale)
	:texModel(texModel), pos(pos), rot(rot), scale(scale)
{
}

Instance::~Instance()
{
}

TexturedModel * Instance::getTexModel() const
{
	return texModel;
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