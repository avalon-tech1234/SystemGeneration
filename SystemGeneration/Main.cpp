#include "Environment.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	size_t n = 5;

	try
	{

#ifdef _DEBUG

		cout << "Generating system... ";
		Environment env(n);
		env.test();
		cout << "finished" << endl;

		/*
		MainTesting letstest(n, env.getFoldername());
		letstest.test_system_generation(FALSE); // тестим для нулевого вектора
		letstest.test_system_generation(TRUE); // тестим для единичного вектора
		for (int i = 0; i < 10; i++)
			letstest.test_system_generation(); // тестим для произвольного вектора
		cout << endl;
		*/
#else

		Environment env(n);
		env.run(true);

#endif

		system("pause");
	}
	catch (std::exception e)
	{
		cout << "Error occupied: " << e.what() << endl << "Program terminated" << endl;
		system("pause");
	}

}
