#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel* model, ImageTexture* texture)
	:model(model), texture(texture)
{
}

TexturedModel::~TexturedModel()
{
}

RawModel * TexturedModel::getModel()
{
	return model;
}

ImageTexture * TexturedModel::getTexture()
{
	return texture;
}