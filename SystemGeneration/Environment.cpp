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
#include "stdafx.h"
#include <experimental/filesystem>
using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;
using namespace filesystem;

Environment::Environment(int n, string _foldername) : n(n), foldername(_foldername)
{
	if (n == 0)
		throw std::exception("Attempt to create equation system with 0 equations. Forbidden");

	create_folder(foldername);

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

}

void Environment::check(const vector<BOOL>& v, const string& text)
{
	std::vector<BOOL> res;
	Reader reader(foldername);
	Transformation P;
	reader.read(P, "P.txt");
	P.substitute(v, res);
	solveSystem(res, res);
	if (v == res) cout << "OK for " << text << endl;
	else cout << "Bad for " << text << endl;
}

void Environment::clean()
{
	remove((foldername + "pre_rand/v1.txt").c_str());
	remove((foldername + "pre_rand/v2.txt").c_str());
	remove((foldername + "pre_rand/M1.txt").c_str());
	remove((foldername + "pre_rand/M2.txt").c_str());
	remove((foldername + "inv/invM1.txt").c_str());
	remove((foldername + "inv/invM2.txt").c_str());
	remove((foldername + "pre_gen/S.txt").c_str());
	remove((foldername + "pre_gen/T.txt").c_str());
	remove((foldername + "pre_gen/F.txt").c_str());
	remove((foldername + "pre_gen/FoT.txt").c_str());
	remove((foldername + "inv/invF.txt").c_str());

	std::experimental::filesystem::remove((foldername + "inv"));
	std::experimental::filesystem::remove((foldername + "pre_gen"));
	std::experimental::filesystem::remove((foldername + "pre_rand"));
}

void Environment::normalizeSystem()
{
	Reader reader(foldername);
	Writer writer(foldername);
	Transformation P;
	reader.read(P, "P.txt");
	P.normalize();
	writer.print(P, "P_norm.txt");

}

void Environment::run(bool print_or_not)
{
	cout << "Generating system..." << endl;
	generateSystem(print_or_not);
	cout << " ...generating system finished" << endl;

	cout << "Solving system...";
	solveSystem(std::vector<BOOL>(n, FALSE), vector<BOOL>{ FALSE });
	cout << " finished" << endl;

	cout << "Normalizing system...";
	normalizeSystem();
	cout << " finished" << endl;

}

void Environment::test()
{
	cout << "Generating system..." << endl;
	generateSystem(true);
	cout << " ...generating system finished" << endl;


	cout << "Solving system...";
	solveSystem(std::vector<BOOL>(n, FALSE), vector<BOOL>{ FALSE });
	cout << " finished" << endl;

	check(std::vector<BOOL>(n, FALSE), "zero vector");
	check(std::vector<BOOL>(n, TRUE), "unit vector");

	std::vector<BOOL> v(n);
	RandomMatrixFactory<BOOL> factory(RandomEngine().getRandomEngine());
	for (int i = 0; i < 10; i++)
	{
		factory.getRandomRow(v);
		string text;
		RowB(v).toString(text, "{", ", ", "}");

		check(v, text);
	}

}

void Environment::generateSystem(bool print_or_not)
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

	MatrixB invM1, invM2; // потребуютс€ позже, при построении решени€
	invM1.initInverse(m1);
	invM2.initInverse(m2);


	if (print_or_not) cout << "finished" << endl << "Generating affine transformation S... ";

	AffineTransformation S = AffineTransformation(m1, v1, print_or_not);
	if (print_or_not) cout << " finished" << endl << "Generating affine transformation T... ";
	AffineTransformation T = AffineTransformation(m2, v2, print_or_not);

	if (print_or_not) cout << " finished" << endl << "Generating random transformation F... ";

	// —троим преобразование F
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
				for (int i = 0; i < prev_num; i++) cout << '\b';
				cout << (i + 1) << '/' << n;
				prev_num = to_string(i + 1).length() + to_string(n).length() + 1;
			}
		}
	}
	if (print_or_not)
		for (int i = 0; i < prev_num; i++)
			cout << '\b';
	prev_num = 0;
	Transformation F;
	builder >> F;
	if (print_or_not) cout << "finished" << endl << "Building inverted F... ";

	// не отход€ от кассы, генерим преобразование, обратное к F
	Transformation invF;
	vector<Polynomial> trans;
	trans.push_back(F[0]);
	for (int i = 1; i < n; i++)
	{
		Polynomial f_i = F[i];
		f_i += {i}; // теперь здесь хранитс€ полином g_i
		Transformation part = vector<Polynomial>{ f_i };
		Transformation x_prev = trans;
		Transformation g_i_x; // g_i (x0, x1, ..., i-1)
		part(x_prev, g_i_x);

		cur = g_i_x[0];
		cur += { i };
		trans.push_back(cur);
		if (print_or_not) {
			for (int i = 0; i < prev_num; i++)
				cout << '\b';
			cout << (i + 1) << '/' << n;
			prev_num = to_string(i + 1).length() + to_string(n).length() + 1;
		}
	}
	if (print_or_not)
		for (int i = 0; i < prev_num; i++) cout << '\b';
	invF = trans;

	if (print_or_not) cout << "finished" << endl << "Building composition P = SoFoT... ";

	// строим итоговое преобразование P
	Transformation FT, P;
	F(T, FT);
	S(FT, P);

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

void Environment::solveSystem(const std::vector<BOOL>& c, std::vector<BOOL>& out, bool print_or_not)
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


	/* ƒалее находим решение уравнени€ –(х) = 0
	 *
	 * ѕользуемс€ формулой:
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
	if (c == std::vector<BOOL>(n, FALSE))
	{
		// форматируем решение (х)
		TransformationBuilder builder;
		for (int i = 0; i < n; i++)
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
