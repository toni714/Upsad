#pragma once

#include "RawModel.h"
#include "ImageTexture.h"

struct TexturedModel
{
	TexturedModel(RawModel* model, ImageTexture* texture) :model(model), texture(texture) {}
	RawModel * model;
	ImageTexture* texture;
};
