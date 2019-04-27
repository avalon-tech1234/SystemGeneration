#include "Matrix.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace matrixes;


// возвращает квадратную матрицу dimension*dimension, заполненную нулями
template <typename t_vattype>
BOOL Matrix<t_vattype>::Init(size_t dimension)
{
	data.clear();
	data.reserve(dimension);

	Row <t_vattype> * row;
	data = std::vector<Row <t_vattype> *>(dimension);

	for (size_t i = 0; i < dimension; i++)
	{
		try {
			row = new Row<t_vattype>(dimension);
		}
		catch (const std::exception&) {
			std::cout << "Ooooppps!";
			return FALSE;
		}

		data[i] = row;

		if (i % 500 == 0)
		{
			// std::cout << i << std::endl;
		}
	}

	return TRUE;
}

template <typename t_vattype>
inline void Matrix<t_vattype>::swap(size_t index1, size_t index2)
{
	std::swap(data[index1], data[index2]);
}


template class Matrix<bool>;
template class Matrix<BOOL>;



