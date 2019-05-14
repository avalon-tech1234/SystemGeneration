#include "Environment.h"
#include <cstdlib>

#include "Reader.h"
#include "Transformation.h"

#include "Parser.h"
#include "TransformationBuilder.h"

using namespace std;
using namespace IO;
using namespace transformations;

using namespace polynomials;


int main()
{
	int n = 5;
	Environment env(n);
	string str = env.run();

	// ������ "��������" ������
	Reader reader(str);
	Transformation F;
	reader.read(F, "F.txt");

	// ������ ������� ������
	Parser parser;
	Polynomial p1, p2;
	parser.read("1", p1);
	parser.read("", p2);

	system("pause");

}
