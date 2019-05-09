#include "Environment.h"

#include "Matrix.h"
#include "RandomMatrixFactory.h"
#include "RandomEngine.h"

using namespace matrixes;
using namespace random;

int main()
{
	int n = 5;
	Environment env(n);

	std::mt19937 gen = RandomEngine().getRandomEngine();
	RandomMatrixFactory<BOOL> matr_factory(gen);
	MatrixB matr, matr2;
	matr_factory.getRandomMatrix(matr, n);

	matr2.initInverse(matr);

	system("pause");

}
