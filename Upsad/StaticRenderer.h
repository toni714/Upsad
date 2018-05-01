#pragma once

#include <map>
#include <vector>

#include "RawModel.h"
#include "Instance.h"
#include "StaticShader.h"

class StaticRenderer {
private:
	std::map<const RawModel*, std::vector<const Instance*>> models;//Model, Instances
	void prepare();
	void prepareModel(const RawModel* model);
	StaticShader shader;
public:
	void addInstance(const Instance* instance);//Swap this for Instance
	void clearQueue();
	void render();
};