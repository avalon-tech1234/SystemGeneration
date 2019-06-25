#include "RandomMatrixFactory.h"
#include <iostream>

using namespace matrixes;
using namespace random;


template <class _T>
void RandomMatrixFactory<_T>::getRandomMatrix(Matrix <_T>& output, int dimension)
{

	output.init_zeros(dimension);

	// генерация обратимой матрицы
	Row <_T>* cur_row;
	for (int i = 0; i < dimension; i++)
	{
		cur_row = output.get(i);

		for (int j = 0; j < dimension; j++)
		{
			if (j < i)
				cur_row->set(j, 0);
			else if (j == i)
				cur_row->set(j, 1);
			else if (j > i)
			{
				int cur = gen() % 2;
				//std::cout << cur << " " << cur % 2 << std::endl;
				cur_row->set(j, toBOOL(cur));
			}
		}
	}

	// перемешивание без потери обратимости
	for (int i = 0; i < dimension; i++)
	{
		int i1, i2;
		i1 = gen() % dimension;
		do i2 = gen() % dimension;
		while (i1 == i2);

		Row<_T>* r1 = output[i1];
		Row<_T>* r2 = output[i2];

		r1-> xor (*r2);
		output.swap(i1, i2);
	}


}

template class RandomMatrixFactory<bool>;
template class RandomMatrixFactory<BOOL>;

