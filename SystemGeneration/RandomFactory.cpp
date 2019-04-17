#include "RandomFactory.h"
#include <cstdlib> // for random
#include <ctime> // for random time

template <class _T>
void RandomFactory<_T>::getRandomRow(Row<_T>* output)
{
	srand((int)time(NULL)); // initialize random seed

	size_t sz = output->size();
	for (size_t i = 0; i < sz; i++)
	{
		output->element(i) = rand() % 2;
	}
}

template <class _T>
void RandomFactory<_T>::getRandomMatrix(Matrix <_T>& output) {

	srand((int)time(NULL)); // initialize random seed

	size_t dimension = output.size();
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
			cur_row->element(j) = rand() % 2;
		}
	}

	for (size_t i = 0; i < dimension; i++)
	{
		Row<_T>* r1 = output.row(rand() % dimension);
		Row<_T>* r2 = output.row(rand() % dimension);
		if (r1 != r2)
			r1-> xor (r2);
	}

	for (size_t i = 0; i < dimension; i++)
	{
		int i1 = rand() % dimension;
		int i2 = rand() % dimension;
		if (i1 != i2)
			output.swap(i1, i2);
	}
}

template class RandomFactory<bool>;
template class RandomFactory<BOOL>;






