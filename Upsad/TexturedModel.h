#pragma once

#include "RawModel.h"
#include "ImageTexture.h"

class TexturedModel
{
private:
	RawModel * model;
	ImageTexture* texture;
public:
	TexturedModel(RawModel* model, ImageTexture* texture);
	~TexturedModel();
	RawModel* getModel();
	ImageTexture* getTexture();
};
