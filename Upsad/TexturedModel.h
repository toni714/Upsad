#pragma once

#include "RawModel.h"
#include "ImageTexture.h"
#include <memory>

struct TexturedModel
{
	TexturedModel(std::shared_ptr<RawModel> model, std::shared_ptr<ImageTexture> texture) :model(model), texture(texture) {}
	std::shared_ptr<RawModel> model;
	std::shared_ptr<ImageTexture> texture;
};
