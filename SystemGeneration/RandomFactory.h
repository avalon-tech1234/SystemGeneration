#pragma once
#include "Matrix.h"

class RandomFactory
{
public:

	// возвращает строку матрицы заданной длиныы
	static void getRandomRow(Row& output, size_t length);

	// возвращает квадратную обратимую матрицу
	static void getRandomMatrix(Matrix& output, size_t dimension);


};