#include "RandomMatrixFactory.h"

using namespace matrixes;
using namespace random;


template <class _T>
void RandomMatrixFactory<_T>::getRandomMatrix(Matrix <_T>& output, size_t dimension)
{

	output.init_zeros(dimension);

	Row <_T>* cur_row;
	for (size_t i = 0; i < dimension; i++)
	{
		cur_row = output.get(i);

		for (size_t j = 0; j < dimension; j++)
		{
			if (j < i) cur_row->set(j, 0);
			if (j == i) cur_row->set(i, 1);
			if (j > i) cur_row->set(j, gen() % 2);
		}
	}

	for (size_t i = 0; i < dimension; i++)
	{
		size_t i1 = gen() % dimension;
		size_t i2 = gen() % dimension;

		Row<_T>* r1 = output[i1];
		Row<_T>* r2 = output[i2];

		if (i1 != i2)
		{
			r1->operator^=(*r2);

			output.swap(i1, i2);
		}
	}
}

template class RandomMatrixFactory<bool>;
template class RandomMatrixFactory<BOOL>;






