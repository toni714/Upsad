#pragma once

#include "RawModel.h"
#include "ImageTexture.h"

class TexturedModel
{
private:
	RawModel * model;
	ImageTexture* texture;
	TexturedModel(RawModel* model, ImageTexture* texture);
public:
	static TexturedModel* loadFromFiles(const char* modelFilename, const char* textureFilename);
	~TexturedModel();
	RawModel* getModel();
	ImageTexture* getTexture();
};
