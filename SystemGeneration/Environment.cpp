#include "Environment.h"

#include "RandomMatrixFactory.h"
#include "RandomPolynomialFactory.h"
#include "RandomEngine.h"
#include "AffineTransformation.h"
#include "TransformationBuilder.h"
#include "speedtest.h"

#include "file_system.h"


#include "Reader.h"
#include "Writer.h"


#include <iostream>
#include <string>
#include <ctime>


using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;

// код проверки на утечки памяти вынесен в speedtest

Environment::Environment(size_t n)
	: n(n), reader(""), writer("")
{
	if (n == 0)
		throw std::exception("Attempt to create equation system with 0 equations. Forbidden");

	foldername = "../results/";

	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	foldername +=
		to_string(now.tm_year + 1900) + "." +
		to_string(now.tm_mon + 1) + "."
		+ to_string(now.tm_mday) + "_"
		+ (now.tm_hour < 10 ? "0" + to_string(now.tm_hour) : to_string(now.tm_hour)) + "."
		+ (now.tm_min < 10 ? "0" + to_string(now.tm_min) : to_string(now.tm_min)) + "."
		+ (now.tm_sec < 10 ? "0" + to_string(now.tm_sec) : to_string(now.tm_sec)) + "/";

	create_folder(foldername);
	create_folder(foldername + "inv/");
	create_folder(foldername + "pre_rand/");
	create_folder(foldername + "pre_gen/");

	reader = Reader(foldername);
	writer = Writer(foldername);
}

void Environment::check(const vector<BOOL>& v, const string& text)
{
	std::vector<BOOL> res;
	P.substitute(v, res);
	solveSystem(res, res);
	if (v == res) cout << "OK for " << text << endl;
	else cout << "Bad for " << text << endl;
}

void Environment::test()
{
	generateSystem(false);
	solveSystem(std::vector<BOOL>(n, FALSE), vector<BOOL>{ FALSE });

	check(std::vector<BOOL>(n, FALSE), "zero vector");
	check(std::vector<BOOL>(n, TRUE), "unit vector");

	for (int i = 0; i < 10; i++)
	{
		// пауза на 1000 мс
		clock_t time_end;
		time_end = clock() + 1000 * CLOCKS_PER_SEC / 1000;
		while (clock() < time_end) { }

		// рандомно генерим v
		std::vector<BOOL> v(n);
		RandomMatrixFactory<BOOL>(RandomEngine().getRandomEngine())
			.getRandomRow(v);

		string text;
		RowB(v).toString(text, "{", ", ", "}");

		check(v, text);
	}
}

void Environment::generateSystem(bool print_or_not)
{
	if (print_or_not) cout << "Performing preparations... ";

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

	TransformationBuilder builder;
	Polynomial cur;
	size_t prev_num = 0;
	for (size_t i = 0; i < n; i++)
	{
		pol_factory.getQuadraticPolynomial(cur, i);
		cur += Monomial(i);
		builder << cur;
		if (print_or_not) {
			if (i % 10 == 0)
			{
				for (size_t i = 0; i < prev_num; i++) cout << '\b';
				cout << i << '/' << n;
				prev_num = to_string(i).length() + to_string(n).length() + 1;
			}
		}
	}
	if (print_or_not)
		for (size_t i = 0; i < prev_num; i++) cout << '\b';
	Transformation F;
	builder >> F;

	if (print_or_not) cout << "finished" << endl << "Building composition SoFoT... ";

	Transformation FT;
	F(T, FT);

	//Transformation P;
	S(FT, P);

	if (print_or_not) cout << "finished" << endl << "Printing into files... ";

	Writer writer(foldername);
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

	if (print_or_not) cout << "finished" << endl;
}

void Environment::solveSystem(const std::vector<BOOL>& c, std::vector<BOOL>& out, bool print_or_not)
{
	RowB v1(n), v2(n);
	MatrixB invM1, invM2;
	Transformation F, invF;
	reader.read(v1, "pre_rand/v1.txt");
	reader.read(v2, "pre_rand/v2.txt");
	reader.read(invM1, "inv/invM1.txt");
	reader.read(invM2, "inv/invM2.txt");
	reader.read(F, "pre_gen/F.txt");

	// генерим преобразование, обратное к F
	vector<Polynomial> trans;
	trans.push_back(F[0]);
	Polynomial cur;
	for (size_t i = 1; i < n; i++)
	{
		Polynomial f_i = F[i];
		f_i += {i}; // теперь здесь хранится полином g_i
		Transformation part = vector<Polynomial>{ f_i };
		Transformation x_prev = trans;
		Transformation g_i_x; // g_i (x0, x1, ..., i-1)
		part(x_prev, g_i_x);

		cur = g_i_x[0];
		cur += { i };
		trans.push_back(cur);
	}
	invF = trans;

	Writer writer(foldername);
	writer.print(invF, "inv/invF.txt");

	/* Далее находим решение уравнения Р(х) = 0
	 *
	 * Пользуемся формулой:
	 * x = invP(0) = invM2 * [ invF( invM1*(c + v1) ) + v2 ], c = 0
	 */

	RowB S_back(n);
	v1 ^= c;
	invM1.multiply(v1, S_back); // S_back = invS = invM1*(c + v1)

	RowB FoS_back(n);
	vector<BOOL> Sb, FSb;
	S_back.toVector(Sb);
	FoS_back.toVector(FSb);
	invF.substitute(Sb, FSb);
	FoS_back = FSb; // FoS_back = inv(SoF) = invF( invM1*(c + v1) )

	FoS_back ^= v2;
	RowB x(n);
	invM2.multiply(FoS_back, x); // FoS_back = invP

	if (c == vector<BOOL>(n, FALSE))
	{
		// форматируем решение (х)
		TransformationBuilder builder;
		for (size_t i = 0; i < n; i++)
		{
			if (x.get(i) == TRUE)
				builder << vector<Monomial> { i, FREE_MEMBER };
			else
				builder << vector<Monomial> { i };
		}
		Transformation solution;
		builder >> solution;

		writer.print(solution, "P_sol.txt");
	}

	x.toVector(out);
}
