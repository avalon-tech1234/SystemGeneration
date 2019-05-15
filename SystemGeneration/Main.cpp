#include "Environment.h"
#include "MainTesting.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	MainTesting letstest;

	size_t n = 5;
	for (int i = 0; i < 10; i++)
	{
		cout << endl << i << " ";
		letstest.test(n, 1); // тестим для единичного вектора
		cout << " ";
		letstest.test(n, 0); // тестим для нулевого вектора
		cout << " ";
		letstest.test(n, -1); // тестим для произвольного вектора
	}
	cout << endl;


	system("pause");

}
