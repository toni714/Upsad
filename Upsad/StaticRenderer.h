#pragma once

#include <map>
#include <vector>

#include "RawModel.h"
#include "Instance.h"
#include "StaticShader.h"
#include "Light.h"

class StaticRenderer {
private:
	std::map<const RawModel*, std::vector<const Instance*>> models;
	void prepare();
	void prepareModel(const RawModel* model);
	void prepareTexture(const ImageTexture* texture);
	void prepareInstance(const Instance* instance);
	StaticShader shader;
	float inc;
public:
	StaticRenderer();
	void addInstance(const Instance* instance);
	void clearQueue();
	void render();
	void render(const Instance* instance);
};