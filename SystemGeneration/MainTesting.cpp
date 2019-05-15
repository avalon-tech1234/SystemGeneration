#include "MainTesting.h"
#include "Environment.h"

#include "Reader.h"
#include "RandomMatrixFactory.h"
#include "RandomEngine.h"
#include "Writer.h"

#include "Matrix.h"
#include "AffineTransformation.h"
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


void MainTesting::test(size_t n, int init_value)
{
	Environment env(n);
	string foldername = env.run(false);

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

	// ������� �������, �������� � �1 � �2
	MatrixB invM1, invM2;
	invM1.initInverse(M1);
	invM2.initInverse(M2);

	// ������� ��������������, �������� � F
	vector<Polynomial> trans;
	trans.push_back(F[0]);
	Polynomial cur;
	for (size_t i = 1; i < n; i++)
	{
		Polynomial f_i = F[i];
		f_i += {i}; // ������ ����� �������� ������� g_i
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

	//cout << "Foldername: " << foldername << endl;

	for (int t = 0; t < 5; t++) {

		// ������� ��������� ������-������ � � c - ��������� ��������������
		vector<BOOL> x(n);
		RandomMatrixFactory<BOOL> fact(RandomEngine().getRandomEngine());
		switch (init_value)
		{
		case 0: break;
		case 1: x = vector<BOOL>(n, TRUE); break;
		default: 
			sleepcp(1000);
			fact.getRandomRow(x, n); 
			break;
		}
		
		vector<BOOL> c(n);
		P_result.substitute(x, c);

		// ������ ������ - ��������� ��������������, ��������� � FoS
		RowB S_back(n), FoS_back(n);
		v1 ^= c;
		invM1.multiply(v1, S_back);
		v1 ^= c; // ������ �� �� �����, ���������� ��� � �������� ���������
		vector<BOOL> Sb, FSb;
		S_back.toVector(Sb);
		FoS_back.toVector(FSb);
		invF.substitute(Sb, FSb);
		FoS_back = FSb;

		FoS_back ^= v2;
		RowB x2(n);
		invM2.multiply(FoS_back, x2);

		// ����, � ������ ������ �������� � � �2=invP(c)=invP(P(x))

		for (size_t i = 0; i < n; i++)
		{
			if (x[i] != x2.get(i))
			{
				cout << " Bad result for x = " + RowB(x).toString();
				return;
			}
		}
		//cout << "Success for x = " + RowB(x).toString() << endl;
		cout << "-";
	}


}

