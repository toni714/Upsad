#pragma once

#include "RawModel.h"

class Instance
{
private:
	RawModel * model;
public:
	Instance(RawModel* model);
	~Instance();

	RawModel* getModel() const;
};

