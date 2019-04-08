#include "RandomFactory.h"
#include <cstdlib> // for random
#include <ctime> // for random time


void RandomFactory::getRandomRow(Row& output, size_t length)
{
	srand((int)time(NULL)); // initialize random seed
	rand(); // пропускаем первое значение, т.к. если вызвать функцию дважды с небольшим промежутком, они могут быть связанны

	Row r(length);
	for (size_t i = 0; i < length; i++)
	{
		r[i] = rand() % 2;
	}

	output = r;
}



void RandomFactory::getRandomMatrix(Matrix& output, size_t dimension)
{
	Matrix matr(dimension);
	



	output = matr;
}


