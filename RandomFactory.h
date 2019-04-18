#pragma once
#include "Matrix.h"
#include <random> 

template <class _T>
class RandomFactory
{
public:

	std::mt19937 gen; // ������� ��������� �����

	// ��������� ������ �������, ����������� ������
	// �� ������ ������ ��������� ���������� ������� (0 � 1)
	void getRandomRow(Row<_T>& output);

	// ��������� ���������� ������� , ����������� ������
	// �� ������ ������� ��������� ���������� ������� (0 � 1). �������������, ��� ��� ��������
	void getRandomMatrix(Matrix <_T>& output, size_t dimension);

	RandomFactory();

};