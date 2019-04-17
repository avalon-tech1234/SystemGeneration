#pragma once
#include "Matrix.h"

template <class _T>
class RandomFactory
{
public:

	// возвращает строку матрицы заданной длиныы
	void getRandomRow(Row<_T>* output);

	// принимает квадратную матрицу , заполненную нулями
	// на выходе матрица заполнена случайными числами. Гарантируется, что она обратима
	void getRandomMatrix(Matrix <_T>& output);

};