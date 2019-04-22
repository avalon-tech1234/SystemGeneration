#include "AffineTransformation.h"
#include "PolynomialBuilder.h"

using namespace std;
using namespace matrixes;
using namespace polynomials;
using namespace transformations;

AffineTransformation::AffineTransformation(const MatrixB& M, const RowB& v)
{
	int n = M.size();
	if (v.size() != n)
		throw exception("Matrix M and vector v for affine transformation must be commensurate");

	PolynomialBilder builder;
	RowB* cur_vec;
	for (int i = 0; i < n; i++)
	{
		cur_vec = M.const_row(i);
		for (int j = 0; j < n; j++)
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

