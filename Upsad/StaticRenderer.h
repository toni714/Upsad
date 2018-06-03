#pragma once

#include <unordered_map>
#include <vector>

#include "RawModel.h"
#include "Instance.h"
#include "StaticShader.h"
#include "Light.h"
#include "Camera.h"

class StaticRenderer {
private:
	std::unordered_map<const RawModel*, std::vector<const Instance*>> queue;
	StaticShader shader;
	float inc;
public:
	StaticRenderer()noexcept;
	void loadProjectionMatrix(const float& fov, const float& screenRatio, const float& nearPlane, const float& farPlane);
	void loadLight(const Light& light);
	void loadCamera(const Camera& camera);
	void addInstance(const Instance* instance);
	void clearQueue();
	void prepare();
	void prepareModel(const RawModel* model);
	void prepareInstance(const Instance* instance);
	void prepareTexture(const ImageTexture* texture);
	void render();
};