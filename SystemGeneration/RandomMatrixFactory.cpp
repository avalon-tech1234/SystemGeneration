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
void RandomMatrixFactory<_T>::getRandomMatrix(Matrix <_T>& output, size_t dimension) {

	output.Init(dimension);

	Row <_T>* cur_row;
	for (size_t i = 0; i < dimension; i++)
	{
		cur_row = output.row(i);
		
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
		Row<_T>* r1 = output.row(gen() % dimension);
		Row<_T>* r2 = output.row(gen() % dimension);
		if (r1 != r2)
			r1-> xor (r2);
	}

	for (size_t i = 0; i < dimension; i++)
	{
		int i1 = gen() % dimension;
		int i2 = gen() % dimension;
		if (i1 != i2)
			output.swap(i1, i2);
	}
}

template class RandomMatrixFactory<bool>;
template class RandomMatrixFactory<BOOL>;






