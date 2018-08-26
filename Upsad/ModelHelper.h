#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "RawModel.h"
#include "ModelData.h"
#include "FileHelper.h"

namespace ModelHelper {
	namespace INTERNAL {
		extern std::unordered_map <std::string, std::shared_ptr<RawModel>> models;
	}
	std::shared_ptr<RawModel> getModelFromFile(const std::string& filename);
	std::shared_ptr<RawModel> loadModelDataToRawModel(const ModelData& modelData);
	void cleanup();
}