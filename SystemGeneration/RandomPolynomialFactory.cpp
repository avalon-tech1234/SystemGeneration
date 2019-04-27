#include  "RandomPolynomialFactory.h"
#include "PolynomialBuilder.h"

using namespace random;
using namespace polynomials;


void RandomPolynomialFactory::addQuadraticPolynomial(Polynomial& out, int n)
{
	PolynomialBuilder builder;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (gen() % 2 == TRUE)
			{
				builder.addGrade(i);
				builder.addGrade(j);
				builder.pushMonomial();
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (gen() % 2 == TRUE)
		{
			builder.addGrade(i);
			builder.pushMonomial();
		}
	}

	if (gen() % 2 == TRUE)
	{
		builder.pushMonomial();
	}

	out += builder.createPolynomial();
}