#include "TextureHelper.h"
#include "OpenGLHelper.h"
#include "FileHelper.h"

std::shared_ptr<ImageTexture> TextureHelper::getTextureFromFile(const std::string& filename)
{
	const auto& texturePosition = INTERNAL::textures.find(filename);
	if (texturePosition != INTERNAL::textures.end()) {
		return texturePosition->second;
	}
	else {
		std::shared_ptr<ImageTexture> texture = loadTextureDataToImageTexture(FileHelper::getBMPDataFromFile(filename));
		INTERNAL::textures.insert(std::make_pair(filename, texture));

		return texture;
	}
}

std::shared_ptr<ImageTexture> TextureHelper::loadTextureDataToImageTexture(const BMPData & textureData)
{
	GLuint textureID = OpenGLHelper::createTexture();
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, textureData.colorFormat, GL_UNSIGNED_BYTE, textureData.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	return std::make_shared<ImageTexture>(textureID);
}

void TextureHelper::cleanup()
{
	INTERNAL::textures.clear();
	//This crashes....
	/*for (auto it = textureData.begin(); it != textureData.end(); it++) {
	delete[] * it;
	}*/
}

std::unordered_map<std::string, std::shared_ptr<ImageTexture>> TextureHelper::INTERNAL::textures= std::unordered_map<std::string, std::shared_ptr<ImageTexture>>();
std::vector<uint8_t*> TextureHelper::INTERNAL::textureData = std::vector<uint8_t*>();