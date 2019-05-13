#pragma once
#include "Matrix.h"

namespace matrixes {
	class MatrixBuilder
	{

	private:
		MatrixB matr;
		size_t n;
		size_t i;

	public:

		MatrixBuilder(size_t n) : n(n), i(0)
		{
			matr.init_zeros(n);
		}

		inline void operator<<(BOOL b)
		{
			if (i < n*n)
			{
				matr[i / n]->set(i%n, b);
				i++;
			}
		}

		inline void operator>>(MatrixB& out)
		{
			out = std::move(matr);
		}

	};
}
