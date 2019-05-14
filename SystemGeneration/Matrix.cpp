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

	// ����� �������� �������, ������ ���������. �� ��������� ������ ������ ����� ����� ��������� �������, � ������ �������� � ��������, ��� � ���������
	init_zeros(n, 2 * n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			get(i)->set(j, matrix[i]->get(j));
		get(i)->set(i + n, 1);
	}

	// ���������� ����������������� �������
	size_t row_num, offset = 0, row_num_top = 0;
	Row<_T>* r0;
	while (offset < n - 1)
	{
		// ������� ������ ��������� ����� � �������, ���� �������� ��� - ���������� �������
		row_num = row_num_top;
		while (row_num < n && data[row_num]->get(offset) == FALSE)
			row_num++;
		if (row_num == n)
		{
			offset++;
			continue;
		}

		// ���� ������ ������ ������� ������� ���� 0, �� ������ ���, ����� �� ���� 1, ���� ��� - ������ �� ��������
		swap(offset, row_num);

		// ��� ������ ������ ����, ���� ������ ������� 1, �������� ������ �� ����� � ������ �������. � ����� �� ���� ������� ���� ����� ����
		r0 = data[offset];
		for (size_t i = offset + 1; i < n; i++)
		{
			if (get(i)->get(offset) == TRUE)
				get(i)->operator^=(r0);
		}

		// ������ ��������� �� �� ����� ��� �������, ���������� ����� ������������ �� ������� ������� ������ � �������� �������
		offset++;
		row_num_top++;
	}

	// ���������� ��������� �������
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

	// ������ "������ ��������" �������
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
		size_t n2 = data[0]->size(); // � �������� ���������� �������� ������� n ����� ���� �� ����� n2

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



