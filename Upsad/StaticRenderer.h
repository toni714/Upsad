#pragma once

#include <map>
#include <vector>

#include "RawModel.h"
#include "Instance.h"
#include "StaticShader.h"
#include "Light.h"

class StaticRenderer {
private:
	std::map<const RawModel*, std::vector<const Instance*>> queue;
	StaticShader shader;
	float inc;
public:
	StaticRenderer();
	void addInstance(const Instance* instance);
	void clearQueue();
	void prepare();
	void prepareModel(const RawModel* model);
	void prepareInstance(const Instance* instance);
	void prepareTexture(const ImageTexture* texture);
	void render();
};