#include "Reader.h"
#include <sstream>
#include "Utility.h"
#include "MatrixBuilder.h"

using namespace IO;
using namespace std;
using namespace matrixes;

void Reader::read(matrixes::MatrixB& matr, std::string filename)
{
	in.open(foldername + filename);

	string cur;
	Utility util;

	// по первой строке (зная, что матрица квадратная) узнаем размерность матрицы
	getline(in, cur);
	util.trim2(cur);
	size_t n = std::count(cur.cbegin(), cur.cend(), ' ') + 1;
	MatrixBuilder builder(n);

	for (int i = 0; i < n; i++)
	{
		if (i != 0) getline(in, cur);
		util.trim2(cur);
		std::stringstream ss(cur);
		while (getline(ss, cur, ',')) {
			util.trim(cur);
			builder << stoi(cur);
		}
	}

	builder.operator>>(matr);

}

void Reader::read(transformations::Transformation& trans, std::string filename)
{
	in.open(foldername + filename);

}




