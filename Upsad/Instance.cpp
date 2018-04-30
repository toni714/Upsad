#include "Instance.h"




Instance::Instance(RawModel * model)
	:model(model)
{
}

Instance::~Instance()
{
}

RawModel * Instance::getModel() const
{
	return model;
}
