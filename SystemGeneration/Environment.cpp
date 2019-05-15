#include "Environment.h"

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



string Environment::run(bool print_or_not) const
{
	if (n == 0)
	{
		cout << "Attempt to create equation system with 0 equations. Forbidden" << endl;
		return "";
	}

	if(print_or_not) cout << "Performing preparations... ";

	std::mt19937 gen = RandomEngine().getRandomEngine();
	RandomMatrixFactory<BOOL> matr_factory(gen);
	RandomPolynomialFactory pol_factory(gen);

	if (print_or_not) cout << "finished" << endl
		<< "Generating random matrixes M1 and M2 and random vectors v1 and v2... ";

	MatrixB m1, m2;
	RowB v1(n), v2(n);
	matr_factory.getRandomMatrix(m1, n);
	matr_factory.getRandomMatrix(m2, n);
	matr_factory.getRandomRow(v1);
	matr_factory.getRandomRow(v2);

	if (print_or_not) cout << "finished" << endl << "Generating affine transformation S... ";

	AffineTransformation S = AffineTransformation(m1, v1);
	if (print_or_not) cout << " finished" << endl << "Generating affine transformation T... ";
	AffineTransformation T = AffineTransformation(m2, v2);

	if (print_or_not) cout << " finished" << endl << "Generating random transformation F... ";

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

	if (print_or_not) cout << "finished" << endl << "Building composition SoFoT... ";

	Transformation FT;
	F(T, FT);

	Transformation P;
	S(FT, P);

	if (print_or_not) cout << "finished" << endl << "Printing into files... ";

	Writer writer;
	writer.print(v1, "v1.txt"); // тестим
	writer.print(v2, "v2.txt"); // тестим
	writer.print(m1, "M1.txt");
	writer.print(m2, "M2.txt");
	writer.print(S, "S.txt");
	writer.print(T, "T.txt");
	writer.print(F, "F.txt");
	writer.print(FT, "FoT.txt");
	writer.print(P, "P.txt");

	if (print_or_not) cout << "finished" << endl;

	return writer.getFoldername();

}