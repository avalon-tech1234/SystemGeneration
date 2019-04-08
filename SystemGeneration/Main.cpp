#include "RandomFactory.h"

#include <iostream>

using namespace std;

int main()
{
	Row r;
	Matrix matr;
	RandomFactory::getRandomRow(r, 5);
	RandomFactory::getRandomMatrix(matr, 30000);

	system("pause");
}