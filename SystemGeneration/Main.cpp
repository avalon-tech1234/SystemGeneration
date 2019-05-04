#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"
#include "speedtest.h"
#include "Writer.h"

#include <iostream>

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;

// код проверки на утечки памяти вынесена в speedtest

int main()
{

	int a = 0;

	cout << "Performing preparations... ";

	size_t n = 5;
	std::mt19937 gen = RandomEngine().getRandomEngine();
	RandomMatrixFactory<BOOL> matr_factory(gen);
	RandomPolynomialFactory pol_factory(gen);

	cout << "finished" << endl 
		<< "Generating random matrixes M1 and M2 and random vectors v1 and v2... ";

	MatrixB m1, m2;
	RowB v1(n), v2(n);
	matr_factory.getRandomMatrix(m1, n);
	matr_factory.getRandomMatrix(m2, n);
	matr_factory.getRandomRow(v1);
	matr_factory.getRandomRow(v2);

	cout << "finished" << endl << "Generating affine transformations S and T... ";

	AffineTransformation S = AffineTransformation(m1, v1);
	AffineTransformation T = AffineTransformation(m2, v2);

	cout << "finished" << endl << "Generating random transformation F... ";

	TransformationBuilder builder;
	Polynomial cur;
	for (size_t i = 0; i < n; i++)
	{
		pol_factory.getQuadraticPolynomial(cur, i);
		cur += Monomial(i);
		builder.addPolynomial(cur);
	}
	Transformation F;
	builder.createTransformation(F);

	cout << "finished" << endl << "Printing into file... ";

	Writer writer;
	writer.printMatrix(m1, "M1.txt");
	writer.printMatrix(m2, "M2.txt");
	writer.printTransformation(S, "S.txt");
	writer.printTransformation(T, "T.txt");
	writer.printTransformation(F, "F.txt");

	cout << "finished" << endl;

	system("pause");

}
