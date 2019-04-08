#pragma once
#include "Matrix.h"

class RandomFactory
{
public:

	// ���������� ������ ������� �������� ������
	static void getRandomRow(Row& output, size_t length);

	// ���������� ���������� ��������� �������
	static void getRandomMatrix(Matrix& output, size_t dimension);


};