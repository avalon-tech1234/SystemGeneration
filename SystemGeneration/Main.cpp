#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"
#include "speedtest.h"
#include "Writer.h"

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;

// проверка на утечки памяти вынесена в speedtest

int main()
{
	size_t n = 3;
	std::mt19937 gen = RandomEngine().getRandomEngine();
	RandomMatrixFactory<BOOL> matr_factory(gen);
	RandomPolynomialFactory pol_factory(gen);

	MatrixB m1, m2;
	RowB v1(n), v2(n);
	matr_factory.getRandomMatrix(m1, n);
	matr_factory.getRandomMatrix(m2, n);
	matr_factory.getRandomRow(v1);
	matr_factory.getRandomRow(v2);

	AffineTransformation S = AffineTransformation(m1, v1);
	AffineTransformation T = AffineTransformation(m2, v2);

	TransformationBuilder builder;
	Polynomial cur;
	for (size_t i = 0; i < n; i++)
	{
		cur = Polynomial(Monomial(i));
		pol_factory.addQuadraticPolynomial(cur, i);
		builder.addPolynomial(cur);
	}
	Transformation F;
	builder.createTransformation(F);


	Writer writer;
	writer.printMatrix(m1, "M1.txt");
	writer.printMatrix(m2, "M2.txt");
	writer.printTransformation(S, "S.txt");
	writer.printTransformation(T, "T.txt");
	writer.printTransformation(F, "F.txt");

}
