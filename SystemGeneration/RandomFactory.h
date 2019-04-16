#pragma once
#include "Matrix.h"

template <class _T>
class RandomFactory
{
public:

	// ���������� ������ ������� �������� ������
	void getRandomRow(Row<_T>& output, size_t length);

	// ���������� ���������� ��������� �������
	void getRandomMatrix(Matrix <_T>& output, size_t dimension);

};