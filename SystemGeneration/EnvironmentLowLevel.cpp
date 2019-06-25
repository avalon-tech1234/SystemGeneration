#include "EnvironmentLowLevel.h"

#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"

#include "Reader.h"
#include "Writer.h"

#include <iostream>

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;

void EnvironmentLowLevel::checkYourself(const vector<BOOL>& v, const string& text)
{
	std::vector<BOOL> res;
	std::vector<BOOL> res2;
	Reader reader(foldername);
	Transformation P;
	reader.read(P, "P.txt");
	P.substitute(v, res); // res = P(v)
	getInvert(res, res2, true); // res2 = invP(res) = invP(P(v))
	if (v == res2) cout << "OK for " << text << endl;
	else cout << "Bad for " << text << endl;
}

void EnvironmentLowLevel::normalizeSystem()
{
	Reader reader(foldername);
	Writer writer(foldername);
	Transformation P;
	reader.read(P, "P.txt");
	P.normalize();
	writer.print(P, "P_norm.txt");

}

void EnvironmentLowLevel::generateSystem(bool print_or_not)
{
	if (print_or_not) cout << "Performing preparations... ";

	IO::Writer writer(foldername);
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

	MatrixB invM1, invM2; // потребуются позже, при построении решения
	invM1.initInverse(m1);
	invM2.initInverse(m2);


	if (print_or_not) cout << "finished" << endl << "Generating affine transformation S... ";

	AffineTransformation S = AffineTransformation(m1, v1, print_or_not);
	if (print_or_not) cout << " finished" << endl << "Generating affine transformation T... ";
	AffineTransformation T = AffineTransformation(m2, v2, print_or_not);

	if (print_or_not) cout << " finished" << endl << "Generating random transformation F... ";

	// Строим преобразование F
	TransformationBuilder builder;
	Polynomial cur;
	size_t prev_num = 0;
	for (int i = 0; i < n; i++)
	{
		pol_factory.getQuadraticPolynomial(cur, i);
		cur += Monomial(i);
		builder << cur;
		if (print_or_not) {
			if ((i + 1) % 10 == 0)
			{
				for (size_t i2 = 0; i2 < prev_num; i2++) cout << '\b';
				cout << (i + 1) << '/' << n;
				prev_num = to_string(i + 1).length() + to_string(n).length() + 1;
			}
		}
	}
	if (print_or_not)
		for (size_t i = 0; i < prev_num; i++)
			cout << '\b';
	prev_num = 0;
	Transformation F;
	builder >> F;
	if (print_or_not) cout << "finished" << endl << "Building inverted F... ";

	// не отходя от кассы, генерим преобразование, обратное к F
	// ti = gi(x0..x(i-1)) + xi => xi = gi(t0..t(i-1)) + ti
	Transformation invF;
	vector<Polynomial> trans = vector<Polynomial>(1, F[0]); // текущее состояние обратного преобразования
	for (int i = 1; i < n; i++)
	{
		Polynomial g_i = F[i]; // зависит от t0..t(i-1)
		g_i += {i};

		Transformation g_i_x; // g_i (x0, x1, ..., x(i-1))
		g_i_x.initComposition(trans, g_i);
		g_i = g_i_x[0]; // зависит уже от x0..x(i-1)

		g_i += { i }; // теперь это выражение для x_i
		trans.push_back(cur);

		if (print_or_not) {
			for (size_t i2 = 0; i2 < prev_num; i2++)
				cout << '\b';
			cout << (i + 1) << '/' << n;
			prev_num = to_string(i + 1).length() + to_string(n).length() + 1;
		}
	}
	if (print_or_not)
		for (size_t i = 0; i < prev_num; i++) cout << '\b';
	invF = trans;

	if (print_or_not) cout << "finished" << endl << "Building composition P = SoFoT... ";

	// строим итоговое преобразование P
	Transformation FT, P;
	FT.initComposition(T, F);
	P.initComposition(FT, S);

	if (print_or_not) cout << "finished" << endl << "Printing into files... ";

	writer.print(v1, "pre_rand/v1.txt");
	writer.print(v2, "pre_rand/v2.txt");
	writer.print(m1, "pre_rand/M1.txt");
	writer.print(m2, "pre_rand/M2.txt");
	writer.print(invM1, "inv/invM1.txt");
	writer.print(invM2, "inv/invM2.txt");
	writer.print(S, "pre_gen/S.txt");
	writer.print(T, "pre_gen/T.txt");
	writer.print(F, "pre_gen/F.txt");
	writer.print(FT, "pre_gen/FoT.txt");
	writer.print(P, "P.txt");
	writer.print(invF, "inv/invF.txt");

	if (print_or_not) cout << "finished" << endl;
}

void EnvironmentLowLevel::solveSystem(bool print_or_not)
{
	std::vector<BOOL> zero(n, FALSE);
	std::vector<BOOL> tmp(1, FALSE);
	getInvert(zero, tmp, false);
}

void EnvironmentLowLevel::getInvert(const std::vector<BOOL>& in, std::vector<BOOL>& out, bool print_to_file_or_not)
{

	RowB v1(n), v2(n);
	MatrixB invM1, invM2;
	Transformation invF;
	IO::Reader reader(foldername);
	IO::Writer writer(foldername);
	reader.read(v1, "pre_rand/v1.txt");
	if (v1.size() == 0)
		throw exception("Cannot read files");
	reader.read(v2, "pre_rand/v2.txt");
	reader.read(invM1, "inv/invM1.txt");
	reader.read(invM2, "inv/invM2.txt");
	reader.read(invF, "inv/invF.txt");


	/* Далее находим решение уравнения Р(х) = 0
	 *
	 * Пользуемся формулой:
	 * x = invP(0) = invM2 * [ invF( invM1*(c + v1) ) + v2 ],
	 * где c = 0 (если решаем; если проверяем, то рандомное)
	 */

	RowB invS(n); // invS(c) = invM1*(c + v1)
	RowB invFS(n); // invF(invS(c))
	RowB invTFS(n);  // invP = invT(invF(invS(c))) = invM2*(invF(invS(c)) + v2)

	v1.xor(in);
	invM1.multiply(v1, invS); 

	vector<BOOL> invS2, res;
	invS.toVector(invS2);
	invF.substitute(invS2, res);
	invFS = res;

	invFS.xor(v2);
	invM2.multiply(invFS, invTFS);

	if (print_to_file_or_not)
	{
		// форматируем решение (х)
		TransformationBuilder builder;
		for (int i = 0; i < n; i++)
		{
			if (invTFS.get(i) == TRUE)
				builder << vector<Monomial> { i, FREE_MEMBER };
			else
				builder << vector<Monomial> { i };
		}
		Transformation solution;
		builder >> solution;

		writer.print(solution, "P_sol.txt");
	}

	invTFS.toVector(out);

}
