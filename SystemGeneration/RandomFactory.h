#pragma once
#include "Matrix.h"

template <class _T>
class RandomFactory
{
public:

	// возвращает строку матрицы заданной длиныы
	void getRandomRow(Row<_T>& output, size_t length);

	// возвращает квадратную обратимую матрицу
	void getRandomMatrix(Matrix <_T>& output, size_t dimension);

};