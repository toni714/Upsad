#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel* model, ImageTexture* texture)
	:model(model), texture(texture)
{
}

TexturedModel * TexturedModel::loadFromFiles(const char * modelFilename, const char * textureFilename)
{
	return new TexturedModel(RawModel::loadFromOBJ(modelFilename), ImageTexture::loadFromBMP(textureFilename));
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