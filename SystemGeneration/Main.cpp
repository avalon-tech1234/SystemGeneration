#include "RandomFactory.h"
#include "Writer.h"
#include <iostream>

using namespace std;

int main()
{
	size_t sz = 2;
	Matrix<BOOL> m;
	m.Init(sz);

	string foldername = Writer::createFolder();

	RandomFactory<BOOL>().getRandomMatrix(m);
	Writer::printMatrix(m, foldername + "/M1.txt");

	RandomFactory<BOOL>().getRandomMatrix(m);
	Writer::printMatrix(m, foldername + "/M2.txt");


}