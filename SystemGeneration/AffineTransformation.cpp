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
	Polynomial cur;
	for (size_t i = 0; i < n; i++)
	{
		cur_vec = M[i];
		for (size_t j = 0; j < n; j++)
		{
			if ((*cur_vec)[j] == TRUE)
			{
				builder.addGrade(j);
				builder.pushMonomial();
			}
		}
		if (v[i] == TRUE)
			builder.pushMonomial();

		builder.createPolynomial(cur); /// ??????
		coordinates.push_back(cur);
	}

}

