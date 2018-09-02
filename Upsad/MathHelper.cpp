#include "MathHelper.h"

#include <random>

float MathHelper::generateRandomFloat()
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_real_distribution<float> dist(0, 1);
	return dist(engine);
}
