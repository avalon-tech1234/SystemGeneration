#include "RandomFactory.h"

int main()
{
	Matrix<BOOL> m;
	Row<bool> r(10);
	RandomFactory<BOOL>().getRandomMatrix(m, 1000);
	RandomFactory<bool>().getRandomRow(r, 10);
}