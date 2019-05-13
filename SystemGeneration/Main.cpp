#include "Environment.h"
#include <cstdlib>

#include "Reader.h"

using namespace std;

int main()
{
	int n = 5;
	Environment env(n);
	string str = env.run();

	IO::Reader rw(str);

	matrixes::MatrixB m;
	rw.read(m, "M1.txt");
	m.print();

	system("pause");

}
