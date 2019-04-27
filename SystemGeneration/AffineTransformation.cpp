#include "AffineTransformation.h"
#include "PolynomialBuilder.h"

using namespace std;
using namespace matrixes;
using namespace polynomials;
using namespace transformations;

AffineTransformation::AffineTransformation(const MatrixB& M, const RowB& v)
{
	size_t n = M.size();
	if (v.size() != n)
		throw exception("Matrix M and vector v for affine transformation must be commensurate");

	PolynomialBuilder builder;
	RowB* cur_vec;
	for (size_t i = 0; i < n; i++)
	{
		cur_vec = M.const_row(i);
		for (size_t j = 0; j < n; j++)
		{
			if (cur_vec->value(j) == TRUE)
			{
				builder.addGrade(j);
				builder.pushMonomial();
			}
		}
		if (v.value(i) == TRUE)
			builder.pushMonomial();
		coordinates.push_back(builder.createPolynomial());
	}

}

