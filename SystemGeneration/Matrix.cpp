#include "Matrix.h"
#include <iostream>

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



template class Matrix<bool>;
template class Matrix<BOOL>;



