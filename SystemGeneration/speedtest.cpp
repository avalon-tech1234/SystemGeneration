

#include <vector>
#include <iostream>
#include <chrono>
#include "BOOL.h"

using namespace std;
using namespace chrono;


// Сравнение скорости выделения памяти и обращения к данным показывает, что использование int вместо bool позволяет сократить расходы по времени примерно на 20-30%

void speedtest()
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

