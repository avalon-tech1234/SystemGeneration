#include "RandomFactory.h"
#include <cstdlib> // for random
#include <ctime> // for random time

template <class _T>
void RandomFactory<_T>::getRandomRow(Row<_T>& output, size_t length)
{
	srand((int)time(NULL)); // initialize random seed
	rand(); // пропускаем первое значение, т.к. если вызвать функцию дважды с небольшим промежутком, они могут быть связанны

	Row<_T> r(length);
	for (size_t i = 0; i < length; i++)
	{
		r.element(i) = rand() % 2;
	}

	output = r;
}

template <class _T>
void RandomFactory<_T>::getRandomMatrix(Matrix <_T>& output, size_t dimension) {

	srand((int)time(NULL)); // initialize random seed
	rand(); // пропускаем первое значение, т.к. если вызвать функцию дважды с небольшим промежутком, они могут быть связанны

	output.Init(dimension);

	Row <_T>* cur_row;
	for (size_t i = 0; i < dimension; i++)
	{
		cur_row = output.row(i);

		cur_row->element(i) = 1;
		for (size_t j = i + 1; j < dimension; j++)
		{
			cur_row->element(j) = rand() % 2;
		}
	}


}

template class RandomFactory<bool>;
template class RandomFactory<BOOL>;






