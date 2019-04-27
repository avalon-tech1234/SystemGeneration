#include "Random.h"
#include <ctime>

using namespace random;

Random::Random()
{
	gen.seed((unsigned int)time(0));
}

const std::mt19937& Random::getRandomEngine() const
{
	return gen;
}
