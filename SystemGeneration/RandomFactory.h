#pragma once
#include "Matrix.h"
#include <random> 

template <class _T>
class RandomFactory
{
public:

	std::mt19937 gen; // генерит случайные числа

	// принимает строку матрицы, заполненную нулями
	// на выходе строка заполнена случайными числами (0 и 1)
	void getRandomRow(Row<_T>& output);

	// принимает квадратную матрицу , заполненную нулями
	// на выходе матрица заполнена случайными числами (0 и 1). Гарантируется, что она обратима
	void getRandomMatrix(Matrix <_T>& output, size_t dimension);

	RandomFactory();

};