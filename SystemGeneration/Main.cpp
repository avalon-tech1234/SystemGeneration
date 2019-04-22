#include "RandomFactory.h"
#include "Writer.h"
#include "AffineTransformation.h"
#include <iostream>

using namespace std;
using namespace matrixes;
using namespace transformations;

int main()
{

	size_t n = 2;
	RandomFactory<BOOL> factory;

	MatrixB m1, m2;
	factory.getRandomMatrix(m1, n);
	factory.getRandomMatrix(m2, n);

	RowB v1(n), v2(n);
	factory.getRandomRow(v1);
	factory.getRandomRow(v2);

	AffineTransformation S = AffineTransformation(m1, v1);
	AffineTransformation T = AffineTransformation(m2, v2);

	Writer writer;
	writer.printMatrix(m1, "M1.txt");
	writer.printMatrix(m2, "M2.txt");
	writer.printAffineTransformation(S, "S.txt");
	writer.printAffineTransformation(T, "T.txt");


}
