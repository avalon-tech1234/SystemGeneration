#include "RandomMatrixFactory.h"

using namespace matrixes;
using namespace random;


template <class _T>
void RandomMatrixFactory<_T>::getRandomRow(Row<_T>& output)
{
	size_t sz = output.size();
	for (size_t i = 0; i < sz; i++)
	{
		output.element(i) = gen() % 2;
	}
}

template <class _T>
void RandomMatrixFactory<_T>::getRandomMatrix(Matrix <_T>& output, size_t dimension)
{

	output.Init(dimension);

	Row <_T>* cur_row;
	for (size_t i = 0; i < dimension; i++)
	{
		cur_row = output.get(i);

		for (size_t j = 0; j < i; j++)
		{
			cur_row->element(j) = 0;
		}
		cur_row->element(i) = 1;
		for (size_t j = i + 1; j < dimension; j++)
		{
			cur_row->element(j) = gen() % 2;
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
			r1->operator^=(r2);

			output.swap(i1, i2);
		}
	}
}

template class RandomMatrixFactory<bool>;
template class RandomMatrixFactory<BOOL>;






