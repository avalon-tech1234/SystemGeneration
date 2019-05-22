#include "MainTesting.h"
#include "Environment.h"

#include "Reader.h"
#include "RandomMatrixFactory.h"
#include "RandomEngine.h"
#include "Writer.h"

#include "Matrix.h"
#include "Polynomial.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;
using namespace polynomials;


void sleepcp(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}


void MainTesting::test_system_generation(BOOL b) const
{
	Reader reader(foldername);
	RowB v1(n), v2(n);
	MatrixB M1, M2;
	Transformation S, T, F, FT, P_result;
	reader.read(v1, "v1.txt");
	reader.read(v2, "v2.txt");
	reader.read(M1, "M1.txt");
	reader.read(M2, "M2.txt");
	reader.read(S, "S.txt");
	reader.read(T, "T.txt");
	reader.read(F, "F.txt");
	reader.read(FT, "FoT.txt");
	reader.read(P_result, "P.txt");

	// генерим матрицы, обратные к М1 и М2
	MatrixB invM1, invM2;
	invM1.initInverse(M1);
	invM2.initInverse(M2);

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
	Transformation invF = trans;

	Writer writer(foldername);
	writer.print(invM1, "invM1.txt");
	writer.print(invM2, "invM2.txt");
	writer.print(invF, "invF.txt");

	// генерим вектор-строку х и c - результат преобразования
	vector<BOOL> x;
	switch (b)
	{
	case TRUE:
		cout << "Testing for unit vector...";
		x = vector<BOOL>(n, b);
		break;
	case FALSE:
		cout << "Testing for zero vector...";
		x = vector<BOOL>(n, b);
		break;
	default:
		cout << "Testing for x = { ";
		sleepcp(1000);
		x = vector<BOOL>(n, 0);
		RandomMatrixFactory<BOOL> fact(RandomEngine().getRandomEngine());
		fact.getRandomRow(x, n);
		for (auto i = x.begin(); i != x.end(); ++i)
			std::cout << *i << ' ';
		cout << "}...";
		break;
	}
	vector<BOOL> c(n);
	P_result.substitute(x, c);

	// строим вектор - результат преобразования, обратного к FoS
	RowB S_back(n), FoS_back(n);
	v1 ^= c;
	invM1.multiply(v1, S_back);
	v1 ^= c; // больше он не нужен, возвращаем его в исходное состояние
	vector<BOOL> Sb, FSb;
	S_back.toVector(Sb);
	FoS_back.toVector(FSb);
	invF.substitute(Sb, FSb);
	FoS_back = FSb;

	FoS_back ^= v2;
	RowB x2(n);
	invM2.multiply(FoS_back, x2);

	// Итак, в данный момент получены х и х2=invP(c)=invP(P(x))

	for (size_t i = 0; i < n; i++)
	{
		if (x[i] != x2.get(i))
		{
			cout << " fail!" << endl;
			return;
		}
	}
	cout << " success!" << endl;



}

