
#include "speedtest.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "BOOL.h"
#include "RandomEngine.h"
#include "RandomMatrixFactory.h"
#include "Windows.h"
#include "conio.h"
#include "Array.h"
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
using namespace chrono;
using namespace matrixes;
using namespace random;

void Testing::test()
{
	cout << "Hello!" << endl;
	int n = 1000000;

	auto start = steady_clock::now();
	vector<bool> v1;
	v1.reserve(n+1);
	v1 = vector<bool>(n);
	auto end = steady_clock::now();
	cout << "Allocation for bool vector took " << duration <double, milli>(end - start).count() << " ms" << endl;

	start = steady_clock::now();
	for (int i = 0; i < n; i++)
	{
		v1[i] = i;
	}
	end = steady_clock::now();
	cout << "Assignment for bool vector took " << duration <double, milli>(end - start).count() << " ms" << endl;

	start = steady_clock::now();
	vector<BOOL> v2;
	v2.reserve(n+1);
	v2 = vector<BOOL>(n);
	end = steady_clock::now();
	cout << "Allocation for BOOL vector took " << duration <double, milli>(end - start).count() << " ms" << endl;

	start = steady_clock::now();
	for (int i = 0; i < n; i++)
	{
		v2[i] = i;
	}
	end = steady_clock::now();
	cout << "Assignment for BOOL vector took " << duration <double, milli>(end - start).count() << " ms" << endl;



	system("pause");
}

void Testing::test2()
{
	int sz = 3000;
	std::mt19937 gen = RandomEngine().getRandomEngine();


	/////////////////////////////////////////////////
	LARGE_INTEGER ST1, ET1, EMls1;
	LARGE_INTEGER ST2, ET2, EMls2;
	LARGE_INTEGER ST3, ET3, EMls3;
	LARGE_INTEGER ST4, ET4, EMls4;

	LARGE_INTEGER Fr;

	QueryPerformanceFrequency(&Fr);

	/////////////////////////////////////////////////

	QueryPerformanceCounter(&ST1);

	Matrix <BOOL> matr_BOOL;
	RandomMatrixFactory<BOOL>(gen).getRandomMatrix(matr_BOOL, sz);

	QueryPerformanceCounter(&ET1);
	EMls1.QuadPart = ET1.QuadPart - ST1.QuadPart;

	EMls1.QuadPart *= 1000000;
	EMls1.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	QueryPerformanceCounter(&ST2);

	Matrix <bool> matr_bool;
	RandomMatrixFactory<bool>(gen).getRandomMatrix(matr_bool, sz);

	QueryPerformanceCounter(&ET2);
	EMls2.QuadPart = ET2.QuadPart - ST2.QuadPart;

	EMls2.QuadPart *= 1000000;
	EMls2.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	BOOL ** array_BOOL;

	QueryPerformanceCounter(&ST3);

	MyArray::AllocateArray(&array_BOOL, sz);

	QueryPerformanceCounter(&ET3);

	EMls3.QuadPart = ET3.QuadPart - ST3.QuadPart;

	EMls3.QuadPart *= 1000000;
	EMls3.QuadPart /= Fr.QuadPart;

	/////////////////////////////////////////////////

	bool ** array_bool;

	QueryPerformanceCounter(&ST4);

	MyArray::AllocateArray(&array_bool, sz);

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

	MyArray::DestroyArray(array_BOOL, sz);
	MyArray::DestroyArray(array_bool, sz);

	/////////////////////////////////////////////////

	system("pause");
}

void Testing::test3()
{
	LARGE_INTEGER ticks;
	std::mt19937 gen;

	QueryPerformanceCounter(&ticks);

	gen.seed(ticks.LowPart ^ ticks.HighPart);

	int cnZero = 0;
	int sz = 100000ui64;
	for (int i = 0;i < sz; i++) {
		if (gen() % 2)
			cnZero++;
	}

	std::cout << "Probability zero = " << ((cnZero / 100000.0) / (sz / 100000.0)) << std::endl;
	_getch();
}

#define _CRTDBG_MAP_ALLOC


void Testing::test_memory_leaks()
{
	static class __init__ {
	public: __init__() { /*_CrtSetBreakAlloc(520);*/
	}
	public: ~__init__() {
		_CrtDumpMemoryLeaks();
	}
	} gl_init;

}
