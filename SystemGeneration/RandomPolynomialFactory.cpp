#include  "RandomPolynomialFactory.h"
#include "PolynomialBuilder.h"

using namespace random;
using namespace polynomials;
using namespace std;

void RandomPolynomialFactory::getQuadraticPolynomial(Polynomial& out, size_t n)
{
	PolynomialBuilder builder;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (gen() % 2 == TRUE)
			{
				builder << i;
				builder << j;
				builder.push();
			}
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		if (gen() % 2 == TRUE)
		{
			builder << i;
			builder.push();
		}
	}

	if (gen() % 2 == TRUE)
	{
		builder.push();
	}

	builder >> out;
}