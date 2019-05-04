#include "AffineTransformation.h"
#include "PolynomialBuilder.h"
#include <iostream>
#include <string>

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
	size_t prev_num = 0;
	for (size_t i = 0; i < n; i++)
	{
		cur_vec = M[i];
		for (size_t j = 0; j < n; j++)
		{
			if (cur_vec->operator[](j) == TRUE)
			{
				builder.addGrade(j);
				builder.pushMonomial();
			}
		}
		if (v[i] == TRUE)
			builder.pushMonomial();

		builder.createPolynomial(cur); /// ??????
		coordinates.push_back(cur);

		if (i % 50 == 0)
		{
			for (int i = 0; i < prev_num; i++) cout << '\b';
			cout << i << '/' << n;
			prev_num = to_string(i).length() + to_string(n).length() + 1;
		}

	}
	for (int i = 0; i < prev_num; i++) cout << '\b';

}

