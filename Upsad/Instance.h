#pragma once

#include "Object3DScaled.h"
#include "TexturedModel.h"

struct Instance :public Object3DScaled {
	Instance(TexturedModel* texturedModel, const glm::vec3& position, const glm::vec3& rotation, float scale) :Object3DScaled(position, rotation, scale), texturedModel(texturedModel) {}
	TexturedModel* texturedModel;//TODO make shared pointer
};
