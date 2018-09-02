#pragma once

#include "ImageTexture.h"
#include "BMPData.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace TextureHelper {
	namespace INTERNAL {
		extern std::unordered_map<std::string, std::shared_ptr<ImageTexture>> textures;
		extern std::vector<uint8_t*> textureData;
	}
	std::shared_ptr<ImageTexture> getTextureFromFile(const std::string& filename);
	std::shared_ptr<ImageTexture> loadTextureDataToImageTexture(const BMPData& textureData);
	void cleanup();

}