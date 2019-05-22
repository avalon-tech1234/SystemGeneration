#include "Environment.h"
#include "MainTesting.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	size_t n = 10;

#ifdef _DEBUG

	cout << "Generating system... ";
	Environment env(n);
	string foldername = env.run(false);
	cout << "finished" << endl;

	MainTesting letstest(n, foldername);
	letstest.test_system_generation(FALSE); // тестим для нулевого вектора
	letstest.test_system_generation(TRUE); // тестим для единичного вектора
	for (int i = 0; i < 10; i++)
		letstest.test_system_generation(); // тестим для произвольного вектора
	cout << endl;

#else

	Environment env(n);
	env.run(true);

#endif

	system("pause");

}
