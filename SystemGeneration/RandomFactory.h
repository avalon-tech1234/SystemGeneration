#pragma once
#include "Matrix.h"

class RandomFactory
{
public:

	// возвращает строку матрицы заданной длиныы
	static void getRandomRow(Row& output, size_t length);

	// возвращает квадратную обратимую матрицу
	static void getRandomMatrix(Matrix& output, size_t dimension);

	template <class _T>
	static void RandomFactory::getRandomMatrix2(Matrix2 <_T>& output, size_t dimension) {
		output.Init(dimension);
	}

};