#include "Matrix.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace matrixes;


template <typename _T>
BOOL Matrix<_T>::init_zeros(size_t dimension, size_t dimension2)
{
	data.clear();
	data.reserve(dimension);

	Row <_T> * row;
	data = std::vector<Row <_T> *>(dimension);

	for (size_t i = 0; i < dimension; i++)
	{
		try {
			row = new Row<_T>(dimension2);
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

template <typename _T>
inline void Matrix<_T>::swap(size_t index1, size_t index2)
{
	auto it1 = data.begin() + index1, it2 = data.begin() + index2;
	iter_swap(it1, it2);
}

template <typename _T>
void Matrix<_T>::initInverse(const Matrix<_T>& matrix)
{
	// TODO


	int n = matrix.size();

	init_zeros(n, 2 * n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			
		}

	}
}






template class Matrix<bool>;
template class Matrix<BOOL>;



