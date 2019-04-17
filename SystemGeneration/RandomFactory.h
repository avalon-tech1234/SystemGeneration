#pragma once
#include "Matrix.h"

template <class _T>
class RandomFactory
{
public:

	// ���������� ������ ������� �������� ������
	void getRandomRow(Row<_T>* output);

	// ��������� ���������� ������� , ����������� ������
	// �� ������ ������� ��������� ���������� �������. �������������, ��� ��� ��������
	void getRandomMatrix(Matrix <_T>& output);

};