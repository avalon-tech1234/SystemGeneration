#include "RandomEngine.h"
#include <ctime>

using namespace random;

RandomEngine::RandomEngine()
{
	gen.seed((int)time(0));
}

const std::mt19937& RandomEngine::getRandomEngine() const
{
	return gen;
}
