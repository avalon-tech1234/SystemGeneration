#include "RandomFactory.h"
#include "Writer.h"
#include <iostream>

using namespace std;

int main()
{

	size_t n = 3;
	RandomFactory<BOOL> factory;

	MatrixB m1, m2;
	factory.getRandomMatrix(m1, n);
	factory.getRandomMatrix(m2, n);

	RowB v1(n), v2(n);
	factory.getRandomRow(v1);
	factory.getRandomRow(v2);

	string s1 = v1.toString();
	string s2 = v2.toString();

	system("pause");
	/*
	string foldername = Writer::createFolder();
	Writer::printMatrix(m1, foldername + "/M1.txt");
	Writer::printMatrix(m2, foldername + "/M2.txt");
	*/

}
