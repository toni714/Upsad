#pragma once

#include <map>
#include <vector>

#include "RawModel.h"

class StaticRenderer {
private:
	std::map<const RawModel*, std::vector<int>> models;//Model, Instances
	void prepare();
	void prepareModel(const RawModel* model);
public:
	void addInstance(const RawModel* model);//Swap this for Instance
	void clearQueue();
	void render();
};