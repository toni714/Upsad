#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color)
	:pos(pos),color(color)
{
}

glm::vec3 Light::getPos() const
{
	return pos;
}

glm::vec3 Light::getColor() const
{
	return color;
}
