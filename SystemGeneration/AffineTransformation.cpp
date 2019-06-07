#include "AffineTransformation.h"
#include "PolynomialBuilder.h"
#include <iostream>
#include <string>

using namespace std;
using namespace matrixes;
using namespace polynomials;
using namespace transformations;

AffineTransformation::AffineTransformation(const MatrixB& M, const RowB& v, bool print_or_not)
{
	size_t n = M.size();
	if (v.size() != n)
		throw exception("Matrix M and vector v for affine transformation have same dimension");

	PolynomialBuilder builder;
	RowB* cur_vec;
	Polynomial cur;
	size_t prev_num = 0;
	for (size_t i = 0; i < n; i++)
	{
		cur_vec = M[i];
		for (size_t j = 0; j < n; j++)
		{
			if (cur_vec->get(j) == TRUE)
			{
				builder << j;
				builder.push();
			}
		}
		if (v.get(i) == TRUE)
		{
			builder.push();
		}

		builder >> cur;
		coordinates.push_back(cur);

		if (i % 50 == 0 && print_or_not)
		{
			for (size_t i = 0; i < prev_num; i++) cout << '\b';
			cout << i << '/' << n;
			prev_num = to_string(i).length() + to_string(n).length() + 1;
		}

	}
	for (size_t i = 0; i < prev_num; i++) cout << '\b';

}

