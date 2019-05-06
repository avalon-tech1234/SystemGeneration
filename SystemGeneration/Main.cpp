#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"
#include "speedtest.h"
#include "Writer.h"

#include <iostream>
#include <string>

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;

// код проверки на утечки памяти вынесен в speedtest

int main()
{

	Polynomial y1(vector<Monomial>{ 0 });
	Polynomial y2({ 0, 1, FREE_MEMBER });
	Polynomial y3({ { 2 },{ 0, 1 } });

	Polynomial t1({ 0, 1, 2, FREE_MEMBER });
	Polynomial t2({ 0, 2, FREE_MEMBER });
	Polynomial t3(vector<Monomial>{ 1, 2 });

	Transformation FF(vector<Polynomial>{ y1, y2, y3 });
	Transformation TT(vector<Polynomial>{ t1, t2, t3 });
	Transformation RES;

	FF(TT, RES);

	cout << "Performing preparations... ";

	size_t n = 100;
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

	cout << "finished" << endl << "Generating affine transformation S... ";

	AffineTransformation S = AffineTransformation(m1, v1);
	cout << " finished" << endl << "Generating affine transformation T... ";
	AffineTransformation T = AffineTransformation(m2, v2);

	cout << " finished" << endl << "Generating random transformation F... ";

	TransformationBuilder builder;
	Polynomial cur;
	size_t prev_num = 0;
	for (size_t i = 0; i < n; i++)
	{
		pol_factory.getQuadraticPolynomial(cur, i);
		cur += Monomial(i);
		builder << cur;
		if (i % 10 == 0)
		{
			for (int i = 0; i < prev_num; i++) cout << '\b';
			cout << i << '/' << n;
			prev_num = to_string(i).length() + to_string(n).length() + 1;
		}
	}
	for (int i = 0; i < prev_num; i++) cout << '\b';
	Transformation F;
	builder >> F;

	cout << "finished" << endl << "Printing into files... ";

	Writer writer;
	writer.printMatrix(m1, "M1.txt");
	writer.printMatrix(m2, "M2.txt");
	writer.printTransformation(S, "S.txt");
	writer.printTransformation(T, "T.txt");
	writer.printTransformation(F, "F.txt");

	cout << "finished" << endl;

	system("pause");

}
