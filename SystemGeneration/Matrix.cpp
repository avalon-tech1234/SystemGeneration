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
	if (index1 != index2)
	{
		auto it1 = data.begin() + index1, it2 = data.begin() + index2;
		iter_swap(it1, it2);
	}
}

template <typename _T>
void Matrix<_T>::initInverse(const Matrix<_T>& matrix)
{
	size_t n = matrix.size();
	if (n == 0) return;

	// слева исходная матрица, справа единичная. По окончании работы метода слева будет единичная матрица, а справа обратная к исходной, что и требуется
	init_zeros(n, 2 * n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			get(i)->set(j, matrix[i]->get(j));
		get(i)->set(i + n, 1);
	}

	// построение верхнетреугольной матрицы
	size_t row_num, offset = 0, row_num_top = 0;
	Row<_T>* r0;
	while (offset < n - 1)
	{
		// находим первое ненулевое число в столбце, если такового нет - пропускаем столбец
		row_num = row_num_top;
		while (row_num < n && data[row_num]->get(offset) == FALSE)
			row_num++;
		if (row_num == n)
		{
			offset++;
			continue;
		}

		// если первое первый элемень первого ряда 0, то меняем так, чтобы он стал 1, если нет - ничего не портится
		swap(offset, row_num);

		// для каждой строки ниже, если первый элемент 1, заменяем строку ее сумму с первой строкой. В итоге во всех строках ниже стоят нули
		r0 = data[offset];
		for (size_t i = offset + 1; i < n; i++)
		{
			if (get(i)->get(offset) == TRUE)
				get(i)->operator^=(r0);
		}

		// теперь проделаем то же самое для матрицы, полученной путем вычеркивания из текущей верхней строки и верхнего столбца
		offset++;
		row_num_top++;
	}

	// построение единичной матрицы
	offset = n - 1;
	while (offset > 0)
	{
		r0 = data[offset];

		row_num = offset - 1;
		while (row_num + 1 >= 1)
		{
			if (data[row_num]->get(offset) == TRUE)
				data[row_num]->operator^=(r0);
			row_num--;
		}

		offset--;
	}

	// взятие "правой половины" матрицы
	for (int i = 0; i < n; i++)
	{
		*get(i) = Row<_T>(vector<_T>(get(i)->begin() + n, get(i)->end()));
	}

}

template <typename _T>
void Matrix<_T>::print() const
{
	if (!data.empty()) {
		size_t n = size();
		size_t n2 = data[0]->size(); // в процессе построения обратной матрицы n может быть не равно n2

		cout << endl << "      ";
		for (size_t i = 0; i < n; i++)
			cout << i << "  ";
		cout << endl << endl;

		for (size_t i = 0; i < n; i++)
		{
			cout << "  " << i << "   ";
			for (size_t j = 0; j < n2; j++)
				cout << data[i]->get(j) << "  ";
			cout << endl;
		}
		cout << endl;
	}
}




template class Matrix<BOOL>;
template class Matrix<bool>;



