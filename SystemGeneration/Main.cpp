#include "RandomFactory.h"

#include <iostream>
#include "Windows.h"

using namespace std;

int main()
{
	Row r;
	Matrix matr;
	RandomFactory::getRandomRow(r, 5);
	//RandomFactory::getRandomMatrix(matr, 200000);

	size_t sz = 10000;

	/////////////////////////////////////////////////
	LARGE_INTEGER ST1, ET1, EMls1;
	LARGE_INTEGER ST2, ET2, EMls2;
	LARGE_INTEGER ST3, ET3, EMls3;
	LARGE_INTEGER ST4, ET4, EMls4;

	LARGE_INTEGER Fr;

	QueryPerformanceFrequency(&Fr);

	/////////////////////////////////////////////////
	
	QueryPerformanceCounter(&ST1);

	Matrix2 <BOOL> matr_BOOL;
	RandomFactory::getRandomMatrix2(matr_BOOL, sz); // сами строки матрицы были битые - что видно при попытке доступа к ним

	QueryPerformanceCounter(&ET1);
	EMls1.QuadPart = ET1.QuadPart - ST1.QuadPart;

	EMls1.QuadPart *= 1000000;
	EMls1.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	QueryPerformanceCounter(&ST2);

	Matrix2 <bool> matr_bool;
	RandomFactory::getRandomMatrix2(matr_bool, sz); // сами строки матрицы были битые - что видно при попытке доступа к ним

	QueryPerformanceCounter(&ET2);
	EMls2.QuadPart = ET2.QuadPart - ST2.QuadPart;

	EMls2.QuadPart *= 1000000;
	EMls2.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	BOOL ** array_BOOL;

	QueryPerformanceCounter(&ST3);

	AllocateArray(&array_BOOL, sz);

	QueryPerformanceCounter(&ET3);

	EMls3.QuadPart = ET3.QuadPart - ST3.QuadPart;

	EMls3.QuadPart *= 1000000;
	EMls3.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	bool ** array_bool;

	QueryPerformanceCounter(&ST4);

	AllocateArray(&array_bool, sz);

	QueryPerformanceCounter(&ET4);

	EMls4.QuadPart = ET4.QuadPart - ST4.QuadPart;

	EMls4.QuadPart *= 1000000;
	EMls4.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	std::cout << "Test for Matrix<BOOL> (mls) = " << EMls1.QuadPart << std::endl;
	std::cout << "Test for Matrix<bool> (mls) = " << EMls2.QuadPart << std::endl;
	std::cout << "Test for BOOL ** (mls) = " << EMls3.QuadPart << std::endl;
	std::cout << "Test for bool ** (mls) = " << EMls4.QuadPart << std::endl;

	/////////////////////////////////////////////////

	DestroyArray(array_BOOL, sz);
	DestroyArray(array_bool, sz);

	/////////////////////////////////////////////////

	system("pause");
}