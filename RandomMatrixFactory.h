#pragma once
#include "Matrix.h"
#include <random> 

namespace random
{

	template <class _T>
	class RandomMatrixFactory
	{
	public:

		std::mt19937 gen; // ������� ��������� �����

		// ��������� ������ �������, ����������� ������
		// �� ������ ������ ��������� ���������� ������� (0 � 1)
		void getRandomRow(matrixes::Row<_T>& output);

		// ��������� ���������� �������, ����������� ������
		// �� ������ ������� ��������� ���������� ������� (0 � 1). �������������, ��� ��� ��������
		void getRandomMatrix(matrixes::Matrix <_T>& output, size_t dimension);

		RandomMatrixFactory(const std::mt19937& gen) : gen(gen) {}

	};

}